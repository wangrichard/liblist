prefix ?= /usr
exec_prefix ?= $(prefix)
libdir ?= $(exec_prefix)/lib
includedir ?= $(prefix)/include

ARCH := $(shell $(CC) -dumpmachine)

CFLAGS += -Iinclude -Wall -Wextra -fPIC

ifeq ($(DEBUG),y)
CFLAGS += -g -O0
DEST=$(ARCH)-debug/
else
CFLAGS += -O2
DEST=$(ARCH)-release/
endif

MAJOR=0
MINOR=1
LIB=liblist.so

LIB_DEST=$(DEST)
OBJ_DEST=$(DEST)/obj/

LIB_SRCS = \
	src/list.c \

LIB_OBJS = $(patsubst %.cpp,$(OBJ_DEST)%.o, $(LIB_SRCS:%.c=$(OBJ_DEST)%.o))
OBJS = $(APP_OBJS) $(LIB_OBJS)

.DEFAULT_GOAL := $(LIB_DEST)$(LIB)
.PHONY: example clean install

all: $(LIB_DEST)$(LIB) example

$(LIB_DEST)$(LIB): $(LIB_OBJS)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(LDFLAGS) -shared -o $@.$(MAJOR).$(MINOR) -Wl,-soname,$(@F).$(MAJOR) $^
	ln -sf $(@F).$(MAJOR).$(MINOR) $@.$(MAJOR)
	ln -sf $(@F).$(MAJOR) $@

example: $(LIB_DEST)$(LIB)
	$(MAKE) -C example

install:
	install -d $(DESTDIR)$(libdir)
	install -m 755 $(LIB_DEST)$(LIB) $(DESTDIR)$(libdir)/$(LIB).$(MAJOR).$(MINOR)
	ln -sf $(LIB).$(MAJOR).$(MINOR) $(DESTDIR)$(libdir)/$(LIB).$(MAJOR)
	ln -sf $(LIB).$(MAJOR) $(DESTDIR)$(libdir)/$(LIB)
	install -d $(DESTDIR)$(includedir)
	install -m 644 include/*.h $(DESTDIR)$(includedir)

clean:
	rm -rf $(DEST)
ifneq ($(wildcard ./example),)
	$(MAKE) -C example clean
endif

-include $(OBJS:.o=.d)

$(OBJ_DEST)%.o: %.c
	@mkdir -p $(@D)
	$(CC) -MMD -MP -c $(CFLAGS) $< -o $@

