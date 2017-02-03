$(MAKECMDGOALS) : run_make

.PHONY: run_make

unexport CC
unexport CXX

mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
current_dir := $(patsubst %/,%,$(dir $(mkfile_path)))

PARTICLE_FIRMWARE?=../spark-firmware
APPDIR=$(abspath $(current_dir))
PLATFORM=photon


include $(PARTICLE_FIRMWARE)/build/platform-id.mk


run_make:
	@$(MAKE) -s -C $(PARTICLE_FIRMWARE)/main \
	PLATFORM=$(PLATFORM) \
	APPDIR=$(APPDIR) \
	USER_MAKEFILE=build.mk \
	BUILD_PATH_BASE=$(APPDIR)/target \
	$(MAKEOVERRIDES) \
	$(MAKECMDGOALS) 
