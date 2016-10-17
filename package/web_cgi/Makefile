

include $(TOPDIR)/rules.mk

PKG_NAME:=web_cgi
PKG_VERSION:=1.0
PKG_RELEASE:=1

PKG_BUILD_DIR := $(BUILD_DIR)/$(PKG_NAME)

include $(INCLUDE_DIR)/package.mk


define Package/web_cgi
  SECTION:=net
  CATEGORY:=Base system
  TITLE:=cgi program for web interface
  DEPENDS:= +libuci
  
endef

define Package/web_cgi/description
  cgi program for web interface
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) ./src/* $(PKG_BUILD_DIR)/
endef

TARGET_CFLAGS += -I$(STAGING_DIR)/usr/include -I$(KERNEL_BUILD_DIR) -I$(KERNEL_BUILD_DIR)/include 
TARGET_LDFLAGS += -L$(STAGING_DIR)/usr/lib -L$(BUILD_DIR_TOOLCHAIN)/uClibc-0.9.33.2/lib

TARGET_CFLAGS += -Wl,--gc-sections

define Build/Compile
	$(MAKE) -C $(PKG_BUILD_DIR) \
	CC="$(TARGET_CC)" \
	CFLAGS="$(TARGET_CFLAGS)" \
	LDFLAGS="$(TARGET_LDFLAGS)" \
	all
endef

define Package/web_cgi/install
	$(INSTALL_DIR) $(1)/usr/mips
	$(INSTALL_DIR) $(1)/usr/mips/cgi-bin
	$(INSTALL_DIR) $(1)/bin/
	$(INSTALL_DIR) $(1)/usr/sbin/
	#$(INSTALL_BIN) $(PKG_BUILD_DIR)/bin/* $(1)/usr/mips/cgi-bin
	
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/cfg $(1)/bin

	$(INSTALL_BIN) $(PKG_BUILD_DIR)/updatefw $(1)/usr/sbin/

	$(INSTALL_BIN) $(PKG_BUILD_DIR)/erase_boot_flag $(1)/usr/sbin/
	
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/set_sys_flag $(1)/usr/sbin/
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/led_ctl $(1)/usr/sbin/

	
endef

$(eval $(call BuildPackage,web_cgi))
