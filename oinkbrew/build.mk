here_files = $(patsubst $(SOURCE_PATH)/%,%,$(wildcard $(SOURCE_PATH)/$1/$2))

INCLUDE_DIRS += $(SOURCE_PATH)/modules
INCLUDE_DIRS += $(SOURCE_PATH)/modules/Adafruit_ILI9341
INCLUDE_DIRS += $(SOURCE_PATH)/modules/Adafruit_mfGFX
INCLUDE_DIRS += $(SOURCE_PATH)/modules/BrewPiTouch
INCLUDE_DIRS += $(SOURCE_PATH)/modules/EEPROM
INCLUDE_DIRS += $(SOURCE_PATH)/modules/LowPassFilter
INCLUDE_DIRS += $(SOURCE_PATH)/screens


CSRC += $(call target_files,oinkbrew,*.c)
CPPSRC += $(call target_files,oinkbrew,*.cpp)

CSRC += $(call target_files,modules,*.c)
CPPSRC += $(call target_files,modules,*.cpp)

CSRC += $(call target_files,screens,*.c)
CPPSRC += $(call target_files,screens,*.cpp)


SRC_EGUI = $(SOURCE_PATH)/modules/eGUI
include $(SRC_EGUI)/egui.mk


$(info source path $(SOURCE_PATH))
LIBS_DIR = $(SOURCE_PATH)/libs
include $(LIBS_DIR)/libs.mk


CFLAGS += -fdata-sections
