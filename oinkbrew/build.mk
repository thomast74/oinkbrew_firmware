here_files = $(patsubst $(SOURCE_PATH)/%,%,$(wildcard $(SOURCE_PATH)/$1/$2))

INCLUDE_DIRS += $(SOURCE_PATH)/modules
INCLUDE_DIRS += $(SOURCE_PATH)/screens


CSRC += $(call target_files,oinkbrew,*.c)
CPPSRC += $(call target_files,oinkbrew,*.cpp)


$(info source path $(SOURCE_PATH))

CFLAGS += -fdata-sections
