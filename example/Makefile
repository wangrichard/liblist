ARCH := $(shell $(CC) -dumpmachine)


LIST_INC?=../include
ifeq ($(LIST_LIB),)
ifeq ($(DEBUG),y)
LIST_LIB=../$(ARCH)-debug/
else
LIST_LIB=../$(ARCH)-release/
endif
endif

LIBS = -llist
LIB_PATHS = -L$(LIST_LIB)

LDFLAGS = $(LIB_PATHS) $(LIBS)
INC = -I$(LIST_INC)

CFLAGS += $(INC) -Wall -Wextra

ifeq ($(DEBUG),y)
DEST = $(ARCH)-debug/
CFLAGS += -g -O0
else
CFLAGS += -O2
DEST = $(ARCH)-release/
endif

APP_DEST = $(DEST)
OBJ_DEST = $(DEST)/obj/

CSRCS += \
	list_test.c \

OBJS = $(CSRCS:%.c=$(OBJ_DEST)%.o)

# all c files are a final program target
all: $(CSRCS:%.c=$(APP_DEST)%)

# magic rule for all .cpp files to be its own program
$(APP_DEST)%: $(OBJ_DEST)%.o
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

# stop it deleting the .o files!
.PRECIOUS: %.c %.o

clean:
	rm -rf $(DEST)

-include $(OBJS:.o=.d)

$(OBJ_DEST)%.o: %.c
	@mkdir -p $(@D)
	$(CC) -MMD -MP -c $(CFLAGS) $< -o $@

