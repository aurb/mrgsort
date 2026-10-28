# Merge and radix sort C functions
# Copyright (C) 2024 Andrzej Urbaniak
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

SORTLIB_SRC := mrgsort.c
SORTLIB_OBJ := $(SORTLIB_SRC:%.c=%.o)
EXAMPLE_SRC := example.c
EXAMPLE_BIN := $(EXAMPLE_SRC:%.c=%)

CC = gcc

CFLAGS := -Wall -Wformat -Werror=format-security
DEBUG_FLAGS := -O0 -g
RELEASE_FLAGS := -O3 -D_FORTIFY_SOURCE=2 -fstack-protector-strong -DNDEBUG
LDFLAGS := 
.PHONY: clean release debug all
all: clean release
release:: CFLAGS += $(RELEASE_FLAGS)
release::
	@echo "Building RELEASE configuration"
release:: $(EXAMPLE_BIN)
	strip --strip-all $^
debug:: CFLAGS += $(DEBUG_FLAGS) #-fsanitize=address -static-libasan ???
debug:: LDFLAGS += #-fsanitize=address
debug::
	@echo "Building DEBUG configuration"
debug:: $(EXAMPLE_BIN)
clean:
	rm -f $(SORTLIB_OBJ) $(EXAMPLE_BIN)

$(EXAMPLE_BIN): $(EXAMPLE_SRC) $(SORTLIB_OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)
$(SORTLIB_OBJ): $(SORTLIB_SRC)
	$(CC) $(CFLAGS) -c $< -o $@

