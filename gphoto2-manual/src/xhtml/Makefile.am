if XMLTOHTML

CLEANFILES = *.html

xhtml_DATA = index.html

index.html: $(gphoto2xml)
	$(XMLTO) xhtml -o . $<

install-data-local: index.html
	$(INSTALL) -d $(DESTDIR)$(xhtmldir)/
	$(INSTALL_DATA) *.html $(DESTDIR)$(xhtmldir)/
	cd $(DESTDIR)$(xhtmldir) && ( [ -d figures ] || (rm -f figures && $(LN_S) -f $(figuredir) figures))
	cd $(DESTDIR)$(xhtmldir) && ( [ -d screenshots ] || (rm -f screenshots && $(LN_S) -f $(screenshotsdir) screenshots))

uninstall-local:
	rm -f $(DESTDIR)$(xhtmldir)/*.html
	rm -f $(DESTDIR)$(xhtmldir)/figures
	rm -f $(DESTDIR)$(xhtmldir)/screenshots
	-rmdir $(DESTDIR)$(xhtmldir)

else

install-data-local:
	@echo "Dummy $@ target"

uninstall-local:
	@echo "Dummy $@ target"

endif
