#TARGET = SysInfo

CFG_TARGET = cfg updatefw set_to_lan led_btn_test




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
set_to_lan:set_to_lan.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ -luci
led_btn_test:led_btn_test.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ -luci

install:
	mkdir bin
	cp -f $(CFG_TARGET) bin/

 
.PHONY: clean
clean:
	rm -f *.o $(TARGET) $(CFG_TARGET)

