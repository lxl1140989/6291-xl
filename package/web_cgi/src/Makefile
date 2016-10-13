#TARGET = SysInfo

CFG_TARGET = cfg updatefw nvram_cfg erase_boot_flag set_sys_flag led_ctl




ifdef ENCRYPT_EN
TARGET += encrypt
endif

XML_CGI_OBJ= main.o cgiget.o cgihandle.o cgipost.o uci_for_cgi.o

all: $(CFG_TARGET) install

# SysInfo: $(XML_CGI_OBJ) nrender_conf.o cfg_api.o
	# $(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ -luci

cfg:cfg.o uci_for_cgi.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ -luci

updatefw:updatefw.o uci_for_cgi.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ -luci

set_sys_flag:set_sys_flag.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^
led_ctl:led_ctl.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^
install:
	mkdir bin
	cp -f $(TARGET) bin/

 
.PHONY: clean
clean:
	rm -f *.o $(TARGET) $(CFG_TARGET)

install:
	mkdir bin
#	cp -f $(TARGET) bin/
#	-cp -f $(TARGET) $(CFG_TARGET) ~

 
.PHONY: clean
clean:
	rm -f *.o $(TARGET) $(CFG_TARGET)

