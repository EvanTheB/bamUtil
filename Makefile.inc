# Makefile that includes this should specify PARENT_MAKE to be
# the Makefile it should include from libStatGen/Makefiles/$(PARENT_MAKE)

#Update version as necessary
VERSION=1.0.14


CURRENT_PATH := $(dir $(lastword $(MAKEFILE_LIST)))
LIB_PATH_GENERAL ?=./libStatGen
LIB_PATH_BAM_UTIL ?= $(LIB_PATH_GENERAL)

# add any additional ../ as necessary if it is a relative path
ACTUAL_PATH := $(if $(filter-out /%,$(LIB_PATH_BAM_UTIL)), \
        $(addprefix $(CURRENT_PATH), $(LIB_PATH_BAM_UTIL)), \
        $(LIB_PATH_BAM_UTIL))
INCLUDE_MAKE := $(ACTUAL_PATH)/Makefiles/$(PARENT_MAKE)

ifneq ($(MAKECMDGOALS),cloneLib)
-include $(INCLUDE_MAKE)
endif

.phony: cloneLib

$(INCLUDE_MAKE):
	@echo Unable to locate: $(INCLUDE_MAKE)
	@echo To change the location, set LIB_PATH_GENERAL or LIB_PATH_BAM_UTIL to the appropriate path to libStatGen.  Or specify \"make LIB_PATH_GENERAL=yourPath\" or \"make LIB_PATH_BAM_UTIL=yourPath\"

