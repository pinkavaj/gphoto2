#include "exif.h"
/*
  EXIF file library for GPHOTO package
  Copyright (C) 1999 Matthew G. Martin

  Generic gphoto implementation and extension by Edouard Lafargue.

  Tag descriptions and an ever-increasing number of structural details
  Taken from "exifdump.py" by Thierry Bousch <bousch@topo.math.u-psud.fr>

  Thanks to Paul Wood <pwood@cs.bris.ac.uk> for sub-ifd parsing.

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.
  
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  
  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/


/***********
 *  Conventions:
 *
 * "tag number" (tagnum) : ID number of a tag (see list just below).
 * "tag index"  (tagind) : index number of a tag inside an EXIF structure
 *                         (for example, tag number one if the first tag, etc..)
 * "tag name" (tagname)  : name of the tag as defined in the EXIF standard.
 */

int exif_debug=0;

/* Size of various tags */
static int exif_sizetab[13]={
  0,1,1,2,4,8,1,1,2,4,8,4,8
};


/**************************************************************/
/*  Utility functions: get fields in little-endian format,    */
/* initialize data structures, etc.                           */
/**************************************************************/

/**
 * Convert to Intel-Endian number.
 *
 * data : pointer to the data to convert
 * size : size of the data to convert
 *
 * Returns : the value
 */
long exif_get_lilend(unsigned char *data, int size){
  long total;

  total=0;
  for (--size;size>=0;size--){
    total<<=8;
    total+=data[size];
  };

  return(total);
};

/**
 * Convert to  signed Intel-Endian number
 */
long exif_get_slilend(unsigned char *data, int size){
  long total;
  long unsigned mask=1<<(size*8-1);

  total=0;
  for (--size;size>=0;size--){
    total<<=8;
    total+=data[size];
  };

  if (total&mask) total-=mask;

  return(total);
};


/**
 *  Return "value" of directory entry at tagind
 */
int gpe_theval(unsigned char *data,int tagind){
 return(exif_get_lilend(data+tagind*12+10,4));
};


/**
 *  Set the "value" of directory entry at tagind.
 */
void gpe_setval(unsigned char *data,int tagind,long newval){
  int i;
  for (i=0;i<4;i++) data[tagind*12+10+i]=0xff&(newval>>(i*8));
  if (gpe_getvalue(data,tagind)!=newval) 
    printf("Setptr: error %d inst %ld\n",gpe_theval(data,tagind),newval);
};


/**
 * Returns the offset of the next IFD entry after
 * offset "num".
 *
 * exif : exif data
 * num  : start offset
 *
 * returns: offset of next IFD.
 */
long exif_next_ifd(unsigned char *exif,int num){

  int offset=(exif[num]+(exif[num+1]<<8))*12+num+2;
  if (exif_debug) printf("next_ifd,offset=%d\n",offset);
  return(exif_get_lilend(exif+offset,4));

}


/**
 * Parse an exif data structure and initialise the "exifparser".
 *
 * exifdat : the exif data
 *
 * returns : size of the rest of the file.
 *           -1 if failed.
 */
int exif_parse_data(exifparser *exifdat) {
  long offset=0;
  ExifData tagdat;

  exif_debug=1;
  /* Check that it's not already preparsed */
  // Doesn't work if we don't initialize this first...
  //  if (exifdat->preparsed) return 0;
  if (exif_debug) printf("Parsing exif structure\n");

  /* First, verify that we really have an EXIF file */
  /* Note: maybe we could also generalize to TIFF... */
  if ((strncmp("Exif",exifdat->header+6,4)) ||
      strncmp("\377\330\377\341",exifdat->header,4)){
    fprintf(stderr,"Not exif data\n");
    return(-1);
  }

  exifdat->exiflen = exifdat->header[5] + (exifdat->header[4]<<8) - 8;
  if (exif_debug) printf("Exif length is %ld\n",exifdat->exiflen);

  /* Count the number of IFD's and register their pointers. */
  exifdat->endian=0;
  if (exifdat->data[0]!='I') {
    exifdat->endian=1;
    printf("%c,Intel-Endian format only supported right now!\n",
	   exifdat->data[0]);
    return(-1);
  };

  offset=exif_get_lilend(exifdat->data+4,4); /*Get offset of first IFD */
  exifdat->ifdcnt=-1;

  /*Step through each IFD */
  do {
    exifdat->ifdcnt++;
    exifdat->ifds[exifdat->ifdcnt]     = exifdat->data+offset;
    exifdat->ifdtags[exifdat->ifdcnt]  = exif_get_lilend(exifdat->data+offset,2);
  } while (offset=exif_next_ifd(exifdat->data,offset));

  exifdat->ifdcnt++;

  /* Look for the EXIF IFD */
  exifdat->preparsed=1; /* Indicate that our exifparser is initialized */
  /* Has to be done before calling exif_get_field */
  if ( ! exif_get_field( EXIF_ExifOffset, 0, exifdat, &tagdat)) {
    printf("No EXIF information stored in this image\n");
  } else {
    if (exif_debug) printf("Offset to the Exif subIFD is %d\n",tagdat.intval);
    exifdat->ifds[exifdat->ifdcnt] = exifdat->data + tagdat.intval;
    exifdat->ifdtags[exifdat->ifdcnt]  = exif_get_lilend(exifdat->data+tagdat.intval,2);
    exifdat->ifdcnt++;
  }

  if (exif_debug) printf("Finished parsing exif structure\n");
  return exifdat->exiflen;
}

/**************************************************************/
/* tag-level functions: get/set tags in the EXIF structure    */
/**************************************************************/

/**
 * Returns the value of a field, identified by its tag and the IFD.
 *
 * Specifying an IFD of '-1' will return the first occurence of
 * the tag in the first IFD where it finds it.
 *
 * tag_number: tag that identifies the field
 * ifd       : image file directory where to look for that tag
 * exifdata  : pointer to the EXIF data
 * tag_data  : filled by this function, contains the actual data
 *
 * returns   : 1 on success, 0 on failure
 */
int exif_get_field( int tag_number, int ifd, exifparser *exifdata, ExifData *tag_data) {
  int numtags,i,j,tag, sign;
  char *ifdp, *offset, *data;

  // Sanity check first:
  exif_debug=1;
  if ( !exifdata->preparsed ) {
    if(exif_parse_data(exifdata) < 0)
      return 0;
  }

  if (ifd == -1) {
    for (i = 0; i < exifdata->ifdcnt+1; i++){
      if (exif_debug) printf("Searching in IFD %d\n",i);
      if ( exif_get_field(tag_number, i, exifdata, tag_data) == 1)
	return 1;
    }
    return 0; // We did not find it.
  } else {

    // Find tag in a specific IFD
    ifdp = exifdata->ifds[ifd];
    numtags=exif_get_lilend(ifdp,2); // How many tags in the IFD
    if (exif_debug)  printf("exif_get_field: %d tags in ifd %d\n",numtags, ifd);
    i=-1;
    do {
      i++;
      tag = exif_get_lilend(ifdp+i*12+2, 2); // Get the tag ID
      // if (exif_debug) fprintf(stderr,"Found tag %d \n",tag);
    } while ((i < numtags) && (tag != tag_number));
    
    if(tag != tag_number) {
      if (exif_debug) fprintf(stderr,"Tag %d not found\n",tag_number);
      return 0;
    }
    
    ifdp = ifdp+i*12+2; // Place pointer at TAG type position
    tag_data->tag = tag;
    tag_data->type = exif_get_lilend(ifdp+2,2);    /* tag type */
    tag_data->size = exif_sizetab[tag_data->type]*exif_get_lilend(ifdp+4,4);
    if (exif_debug) printf("(%d bytes) ",tag_data->size);

    ifdp += 8; // place pointer at beginning of the contents of the field

    /* Data types smaller than 4 bytes are stored directly in
       the IFD field value. Otherwise, that value is an offset
       to the real data */
    if (tag_data->size > 4) {
	ifdp = exifdata->data + exif_get_lilend(ifdp,4);
    }

    /* Last operation, get the data itself: */
    /* Allocate memory, and copy the data */
      data=malloc(tag_data->size);
      if (data==NULL){
	fprintf(stderr,"exif_get_field: could not malloc\n");
	return 0;
      };

    if (tag_data->type == EXIF_ASCII) {
	memcpy(data,ifdp,tag_data->size);  // Normally, the exif data includes a terminating 0
	tag_data->data = data;
	if(exif_debug) printf("\"%s\"",data);
    } else {
      for (i = 0; i < tag_data->size; i += exif_sizetab[tag_data->type]) {
	//if (exif_debug) fprintf(stderr,".");
	if ( tag_data->type % 5 ) {
	  memcpy(data+i,ifdp+i,exif_sizetab[tag_data->type]);	  
	} else { // Fraction
	    tag_data->num =exif_get_lilend(ifdp+i,4);
	    tag_data->den =exif_get_lilend(ifdp+i+4,4);
	  
	  if(exif_debug)  printf("%d/%d=%.3g ",tag_data->num,
		                  tag_data->den,
				 (tag_data->den==0)?0:(1.0*tag_data->num/tag_data->den));
	}	
      }
      // If the value can be put into an int, save the trouble and store
      // it into "intval" right away...
      if(tag_data->type != EXIF_ASCII && tag_data->type != EXIF_RATIONAL &&
	 tag_data->type != EXIF_UNDEFINED && tag_data->type != EXIF_SRATIONAL) {
	tag_data->intval = exif_get_lilend(data,exif_sizetab[tag_data->type]);
	if(exif_debug) printf("'%d'",tag_data->intval);
      }
      tag_data->data = data; // Save the data field
    }
    if (exif_debug) printf("\n"); /*end of this tag */
    return 1;
  }
  return 0;
}

/**
 * Gets an ASCII tag.
 *
 * Specifying an IFD of '-1' will return the first occurence of
 * the tag in the first IFD where it finds it.
 *
 * tag_number: tag that identifies the field
 * ifd       : image file directory where to look for that tag
 * exifdata  : pointer to the EXIF data
 *
 * returns   : pointer to the tag value.
 */
char * exif_get_ascii_field( int tag_number, int ifd, exifparser *exifdat) {
  ExifData tagdat;

  if (exif_parse_data(exifdat)<0) return NULL;

  if ( ! exif_get_field( tag_number, ifd, exifdat, &tagdat)) {
    if (exif_debug) printf("No comment field in this image\n");
    return NULL;
  } else {
    return tagdat.data;
  }
}

/**
 * Gets a numeric tag.
 *
 * Specifying an IFD of '-1' will return the first occurence of
 * the tag in the first IFD where it finds it.
 *
 * tag_number: tag that identifies the field
 * ifd       : image file directory where to look for that tag
 * exifdata  : pointer to the EXIF data
 *
 * returns   : tag value.
 */
int exif_get_int_field( int tag_number, int ifd, exifparser *exifdat) {
  ExifData tagdat;
  int tmp;

  if (exif_parse_data(exifdat)<0) return 0;

  if ( ! exif_get_field( tag_number, ifd, exifdat, &tagdat)) {
    if (exif_debug) printf("Field not found in this image.\n");
    return 0;
  } else {
    tmp = tagdat.intval;
    free(tagdat.data);   // ???
    return tmp;
  }  
  return 0;

}


/**
 * Returns the name of a given tag number
 */
char *exif_get_tagname(int tag_number) {
  int i=-1;
  do {
    i++;
    if (tagnames[i].num == tag_number) return (tagnames[i].desc);
  } while (tagnames[i].num);
  return("Unknown");  
}

/**************************************************************/
/* Higher-level functions: get/set logical entities, such as  */
/* comments, thumbnail, etc.                                  */
/**************************************************************/

/**
 * Gets the comment field if it exists.
 */
int exif_get_comment(exifparser *exifdat, char *comment) {
  ExifData tagdat;

  if (exif_parse_data(exifdat)<0) return 0;

  /* User Comment is in IFD number 2 */
  if ( ! exif_get_field( EXIF_UserComment, 2, exifdat, &tagdat)) {
    if (exif_debug) printf("No comment field in this image\n");
    return 0;
  } else {
    comment = tagdat.data;
    return tagdat.size;
  }  
  return 0;
}

/**
 * Sets the comment field if it exists.
 */
int exif_set_comment(exifparser *exifdat, char *comment) {
  return 0;
}

/**
 * Gets the thumbnail of an EXIF image.
 *
 * The returned thumbnail might be in JPEG or TIFF format.
 */
unsigned char *exif_get_thumbnail(exifparser *exifdat) {
  char *tmpstr[32];
  unsigned char *imagedata,*exifimg,*newimg,*curptr;
  unsigned int exiflen,entry;
  long dataptr,dsize,tag,datvec,size,tmp;
  int i,j;

  exif_debug=1;
  if (exif_parse_data(exifdat)<0) return(NULL);

  newimg=malloc(exifdat->exiflen);
  if (newimg==NULL){
    fprintf(stderr,"exif_get_thumbnail: could not malloc\n");
    return(NULL);
  };

  /* Copy header*/
  memcpy(newimg,exifdat->data,8);
  curptr=newimg+8;

  if (exif_debug) {    
      ExifData owner;
      char *comment;
      printf("Decoding EXIF fields in thumbnail\n");
      exif_get_field( EXIF_Model, -1, exifdat, &owner);
      printf("Camera model: %s\n",owner.data);
      printf("Comment for this picture (%d chars)",exif_get_comment( exifdat, comment));
      //printf(" -> %s\n",comment); Not OK on Linux
      exif_get_field( EXIF_SubjectDistance, 2, exifdat, &owner);
      //      dump_exif(exifdat);      
  };

  /* Skip to Thumbnail image data */
  if(exifdat->ifdcnt<2) {
    if (exif_debug) {
      fprintf(stderr,"Too few ifds, doesn't look right. Giving up\n");
    };
    return(NULL); /* Things don't look right...*/
  };

  /* Jump to thumbnail image data */
  exifimg=exifdat->ifds[1];

  /* Copy number of entries */
  memcpy(curptr,exifimg,2);
  curptr+=2;

  entry=exif_get_lilend(exifimg,2);

  if (exif_debug) printf("Entry is %d \n",entry);

  /* See if thumb is a JPEG */
  tmp=gpe_getintval(exifimg,EXIF_JPEGInterchangeFormat); /*imagedata start*/
  if (tmp>0) { /* jpeg image */
    if (exif_debug) fprintf(stderr,"Found jpeg thumb data\n");
    dsize=gpe_getintval(exifimg,EXIF_JPEGInterchangeFormatLength);
    if (dsize==-1){
      fprintf(stderr,"No Jpeg size tag for thumbnail, skipping\n");
      return(NULL);
    };
    imagedata=exifdat->data+tmp;
    memcpy(newimg,imagedata,dsize);
    return(newimg);
  };

  /* Try a TIFF */
  tmp=gpe_getintval(exifimg,EXIF_StripOffsets); /*imagedata start*/
  if (tmp==-1) {
    fprintf(stderr,"gpe_get_thumbnail: Tiff or jpeg data not found, skipping\n");
    return(NULL);
  };
  imagedata=exifdat->data+tmp;

  dataptr=gpe_getintval(exifimg,EXIF_StripByteCounts);        /* imagedata size */
  if (dataptr==-1) {
    printf("Split two\n");
    return(NULL);
  };

  if (exif_debug) printf("Imagedata size is %ld bytes\n",dataptr);

  for (i=0;i<entry;i++){
    dsize=gpe_datsize(exifimg,i);
    tag=gpe_tagnum(exifimg,i);

    /*
      if (exif_debug) printf("Datsize %d (tag=%ld) is %ld\n",i,tag,dsize);
    */

    if (tag==EXIF_StripOffsets) {
      gpe_setval(exifimg,i,12*entry+14); /* set to end of directory */
      memcpy(curptr,exifimg+12*i+2,12);
      curptr+=12;
    }
    else {
      if (dsize<5){
	/* Just copy the field if small */
        memcpy(curptr,exifimg+12*i+2,12);
	curptr+=12;
      }
      else {
	datvec=gpe_getvalue(exifimg,i);
	gpe_setval(exifimg,i,dataptr+12*entry+14);
	for (j=0;j<dsize;j++) imagedata[dataptr++]=exifdat->data[datvec+j];
        memcpy(curptr,exifimg+12*i+2,12);
	curptr+=12;
      };
    };
  };
  memcpy(curptr,exifimg+12*entry+10,4); /* Write 4 zero bytes */
  curptr+=4;
  memcpy(curptr,imagedata,dataptr);/* ? */
  curptr+=dataptr;
  return newimg;

  return 0;
}

/**
 * Return tag number of directory entry at tag index
 *
 * data   : pointer to EXIF data, aligned to the beginning of an IFD
 * tagind : index of the tag within the IFD
 *
 * returns: tag ID number
 */
int gpe_tagnum( char *data,int tagind){
 return(exif_get_lilend(data+tagind*12+2,2));
};

/**
 * Get the value of a tag as an integer.
 * only works for 4 byte values.
 *
 * data : exif data, aligned to the beginning of an IFD.
 * tagnum : tag number.
 *
 * returns: -1 if the tag is not found.
 */
int gpe_getintval(unsigned char *data, int tagnum) {
  int numtags,i,tag,tagtype;

  numtags=exif_get_lilend(data,2);

  if (exif_debug)  printf("getval:%d tags\n",numtags);

 i=-1;
 do {
   i++;
   tag=exif_get_lilend(data+i*12+2,2);
 } while ((i<numtags) && (tag!=tagnum));

 if(tag!=tagnum) {
   if (exif_debug) fprintf(stderr,"Tag %d not found\n",tagnum);
   return(-1);
 };

 tagtype=exif_get_lilend(data+i*12+4,2);    /* tag type */

 return(exif_get_lilend(data+i*12+10,exif_sizetab[tagtype-1]));
};

/**
 *  Return "value" of directory entry at tagind
 *
 * data  : exif data
 * tagind: tag index
 */
int gpe_getvalue(unsigned char *data,int tagind){
 return(exif_get_lilend(data+tagind*12+10,4));
};


/**
 * Add all tag names and values in an ifd to an array of strings for gphoto
 */
//int gpe_exif_add_all(exifparser *exifdata,int ifdnum,char **datastrings){
//  int i;
//  for (i=0;i<exifdata->ifdtags[ifdnum];i++){
//    togphotostr(exifdata,ifdnum,i,datastrings+i*2,datastrings+i*2+1);
//    /*    printf("%s = %s\n",datastrings[i*2],datastrings[i*2+1]);*/
//  };
//};



int gpe_dump_ifd(int ifdnum,exifparser *exifdata,char **allpars){
  int i,j,tag,numtags,tagtype,count,typelen, value,tmp1,tmp2;
  char tmpstr[256];
  unsigned char* thistag;
  unsigned char* thedata;
  unsigned char* thisisd;
  char tmpdat[200];
  char** name;
  
  
    thisisd=exifdata->ifds[ifdnum];
    numtags=exif_get_lilend(thisisd,2);
    printf("has %d tags ----------------------\n",numtags);
    for (i=0;i<numtags;i++){

      thistag=thisisd+i*12+2;   /* pointer to data for this tag */

      tag=exif_get_lilend(thistag,2);          /* tag identifier */
      tagtype=exif_get_lilend(thistag+2,2);    /* tag type */
      count = exif_get_lilend(thistag+4, 4);   /* how many */
      typelen=exif_sizetab[tagtype];/* length of this type */

      if (exif_debug) printf("(%dX) ",count);

      thedata=thistag+8;
      if (count*typelen > 4)   /* find it in a data block elsewhere */
	thedata = exifdata->data+exif_get_lilend(thistag+8, 4);

      printf("Tag 0x%X %s = ",tag,exif_get_tagname(tag));

      if (tagtype==2) {
	/* Do an ASCII tag */
	  strncpy(tmpstr,thedata,count+1);
	  tmpstr[count+1]='\0';
	  printf("'%s'",tmpstr);
	} 
      else for (j=0;j<count;j++) {

	if ((tagtype==5)||(tagtype==10)) {/* Fractional */
	  tmp1=exif_get_slilend(thedata+j*typelen,4);
	  tmp2=exif_get_slilend(thedata+4+j*typelen,4);
	      printf("%d/%d=%.3g ",tmp1,tmp2,(tmp2==0)?0:(1.0*tmp1/tmp2));
	}
	else {
	  value =exif_get_lilend(thedata+j*typelen,typelen);
	  printf("%d ",value);
	};
	
      };

      printf("\n"); /*end of this tag */

/* Print SubIfd tags */
      if ( tag == 0x8769 ) {
         printf("Exif SubIFD at offset %d\n", value );
         exifdata->ifds[exifdata->ifdcnt]     = exifdata->data+value;  
         exifdata->ifds[exifdata->ifdcnt];
         exifdata->ifdtags[exifdata->ifdcnt]=exif_get_lilend(exifdata->data+value,2);
         exifdata->ifdcnt++;

}
/***/

    };
};



/* Walk through EXIF structure, printing values */
int gpe_dump_exif(exifparser *exifdata){ 
  int i,tag;
  unsigned char* thisifd;

  if (!exifdata->preparsed) 
    if (stat_exif(exifdata)) return(-1);

  for (i=0;i<exifdata->ifdcnt;i++){
    switch (i) {
       case 0:      
          printf("IFD %d, %s ",i,"Main Image");
          break;
       case 1:
          printf("IFD %d, %s ",i,"Thumbnail");
         break;
       case 2:
          printf("IFD %d, %s ",i,"Sub IFD");
          break;
   
   }       
       

    gpe_dump_ifd(i,exifdata,NULL);
  };
};

/**
 * Return data size of directory entry at tagind
 */
int gpe_datsize(unsigned char *data,int tagind){
  return(exif_sizetab[exif_get_lilend(data+tagind*12+4,2)]*exif_get_lilend(data+tagind*12+6,4));
};
