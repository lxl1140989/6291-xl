#
# Copyright (C) 2009-2010 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#
include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/image.mk
PRODUCT_MODEL=ORICO_2566

JFFS2_BLOCKSIZE=32k 512k

ifneq ($(CONFIG_TARGET_xburst_qi_lb60),)
UBI_OPTS = -m 4096 -p 512KiB
UBIFS_OPTS = -m 4096 -e 516096 -c 4095
else
UBI_OPTS = -m 2048 -p 128KiB -s 512
UBIFS_OPTS = -m 2048 -e 126KiB -c 4096
endif

UIMAGE:=$(BIN_DIR)/$(IMG_PREFIX)-uImage.bin

define kernel_entry
0x$(shell $(TARGET_CROSS)nm $(1) 2>/dev/null | grep " kernel_entry" | cut -f1 -d ' ')
endef


define MkImageGzip
	gzip -9 -c $(1) > $(1).gz
	mkimage -A mips -O linux -T kernel -a 0x80010000 -C gzip \
		-e $(call kernel_entry,$(KDIR)/vmlinux.debug) -n '$(PRODUCT_MODEL)' \
		-d $(1).gz $(2)
endef

define MkImageLzma
	lzma e $(1) -lc1 -lp2 -pb2 $(1).lzma
	mkimage -A mips -O linux -T kernel -a 0x80010000 -C lzma \
		-e $(call kernel_entry,$(KDIR)/vmlinux.debug) -n '$(PRODUCT_MODEL)' \
		-d $(1).lzma $(2)
endef

define Image/BuildKernel
	$(call MkImageGzip,$(KDIR)/vmlinux,$(UIMAGE))
	$(call MkImageLzma,$(KDIR)/vmlinux,$(UIMAGE).lzma)
endef

define Image/Build/squashfs
	$(call prepare_generic_squashfs,$(KDIR)/root.squashfs)
endef


NOR_16MB=6291-nor-16MB.bin
NOR_UPDATE_FW=6291-nor-update-fw.bin
define Image/Build

ifeq ($(1),squashfs)
	$(STAGING_DIR_HOST)/bin/padjffs2 $(KDIR)/root.squashfs 32
endif
	dd if=$(KDIR)/root.$(1) of=$(BIN_DIR)/$(IMG_PREFIX)-root.$(1) bs=128k conv=sync
ifeq ($(1),squashfs)
	rm -rf $(BIN_DIR)/$(NOR_16MB)
	rm -rf $(BIN_DIR)/$(NOR_UPDATE_FW)

	if [ `stat -c%s "$(TOPDIR)/uboot/uboot-6291-norboot.bin"` -gt 196608 ]; then \
		echo "Error: $(TOPDIR)/uboot/uboot-6291-norboot.bin is too big" >&2; \
		exit 1; \
	fi
	
	#2097120=2M-32(MD5)
	if [ `stat -c%s "$(BIN_DIR)/$(IMG_PREFIX)-uImage.bin.lzma"` -gt 2097120 ]; then \
		echo "Error: $(BIN_DIR)/$(IMG_PREFIX)-uImage.bin.lzma is too big" >&2; \
		exit 1; \
	fi
	#0x9B0000
	if [ `stat -c%s "$(BIN_DIR)/$(IMG_PREFIX)-root.$(1)"` -gt 10158080 ]; then \
		echo "Error: $(BIN_DIR)/$(IMG_PREFIX)-root.$(1) is too big" >&2; \
		exit 1; \
	fi
	#4M
	if [ `stat -c%s "$(TOPDIR)/mk_x1000_bin/backup-system-nor-update-fw.bin"` -gt 4194304 ]; then \
		echo "Error: $(TOPDIR)/mk_x1000_bin/backup-system-nor-update-fw.bin is too big" >&2; \
		exit 1; \
	fi
	
	dd if=$(BIN_DIR)/$(IMG_PREFIX)-uImage.bin.lzma of=$(BIN_DIR)/uImage_tmp.bin  bs=1k conv=notrunc count=256
	md5sum $(BIN_DIR)/uImage_tmp.bin | cut -d ' ' -f1 > $(BIN_DIR)/uImage_md5_tmp.txt
	
	#0xBB0000
	tr '\000' '\377' < /dev/zero | dd of=$(BIN_DIR)/$(NOR_UPDATE_FW) bs=1024 count=11968 status=noxfer
	dd if=$(BIN_DIR)/$(IMG_PREFIX)-uImage.bin.lzma of=$(BIN_DIR)/$(NOR_UPDATE_FW) conv=notrunc status=noxfer
	dd if=$(BIN_DIR)/$(IMG_PREFIX)-root.$(1) of=$(BIN_DIR)/$(NOR_UPDATE_FW) bs=1M seek=2 conv=notrunc status=noxfer
	dd if=$(BIN_DIR)/uImage_md5_tmp.txt of=$(BIN_DIR)/$(NOR_UPDATE_FW) seek=2097120 bs=1 conv=notrunc count=32
	
	tr '\000' '\377' < /dev/zero | dd of=$(BIN_DIR)/$(NOR_16MB) bs=1024 count=16384 status=noxfer	
	dd if=$(TOPDIR)/uboot/uboot-6291-norboot.bin of=$(BIN_DIR)/$(NOR_16MB) conv=notrunc status=noxfer
	#dd if=$(BIN_DIR)/$(IMG_PREFIX)-uImage.bin.lzma of=$(BIN_DIR)/$(NOR_16MB) bs=1024 seek=256 conv=notrunc status=noxfer
	#dd if=$(BIN_DIR)/$(IMG_PREFIX)-root.$(1) of=$(BIN_DIR)/$(NOR_16MB) bs=1024 seek=2304 conv=notrunc status=noxfer
	dd if=$(BIN_DIR)/$(NOR_UPDATE_FW) of=$(BIN_DIR)/$(NOR_16MB) bs=1024 seek=256 conv=notrunc status=noxfer
	dd if=$(TOPDIR)/mk_x1000_bin/backup-system-nor-update-fw.bin of=$(BIN_DIR)/$(NOR_16MB) bs=1024 seek=12224 conv=notrunc status=noxfer
	
	rm $(BIN_DIR)/uImage_tmp.bin 
	rm $(BIN_DIR)/uImage_md5_tmp.txt
	#sync
	
endif

endef

$(eval $(call BuildImage))
