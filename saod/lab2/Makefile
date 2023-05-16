APP_NAME = app
OBJ = obj/hashtab.o obj/btree.o obj/main.o 
LIB  = obj/hashtab.a obj/btree.a
CFLAGS = -Wall 
DEPSFLAGS = -MMD 
GDB = -g 

DEPS = $(OBJ:.o=.d)
-include $(DEPS)
.PHONY: all clean run
all: $(APP_NAME)

$(APP_NAME): $(OBJ) 
	$(CC) $(CFLAGS) $(GDB) $(DEPSFLAGS) -o $@ $^
obj/%.o: src/%.c 
	$(CC) $(CFLAGS)  $(GDB) $(DEPSFLAGS) -c $< -o $@
clean:
	rm -rf $(APP_NAME) obj/*.o obj/*.d
run:
	./$(APP_NAME)
