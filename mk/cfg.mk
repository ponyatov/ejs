CFLAGS += -I$(INC) -I$(TMP)
CFLAGS += -I$(CWD)/hw/$(HW)/inc -I$(CWD)/os/$(OS)/inc
CFLAGS += -O0 -ggdb
CFLAGS += -D$(shell echo $(OS)|tr a-z A-Z)
CFLAGS += -D$(shell echo $(HW)|tr a-z A-Z)
