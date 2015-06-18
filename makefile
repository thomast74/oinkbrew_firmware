$(MAKECMDGOALS): run_make

.PHONY: run_make

APPDIR = ../../oinkbrew_firmware


run_make:
	@$(MAKE) -e -C ../spark-firmware/main \
	APPDIR=$(APPDIR) \
	USER_MAKEFILE=build.mk \
	TARGET_FILE=oinkbrew \
	TARGET_DIR=$(APPDIR)/target \
	SPARK_CLOUD=n \
	$(MAKEOVERRIDES) \
	$(MAKECMDGOALS) 
