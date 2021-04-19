all: serialize deserialize

obj/%.o: %.cpp student.h
	$(CXX) -c $< -o $@

serialize: obj/serialize.o
	$(CXX) -o $@ $^

deserialize: obj/deserialize.o
	$(CXX) -o $@ $^

clean:
	rm -f obj/*.o
	rm -f serialize deserialize file.bin
