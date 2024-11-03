export opts=-D_FORTIFY_SOURCE=2 -fno-diagnostics-show-option	\
-fstack-protector-all -g -O3 -std=c++2a -Walloc-zero -Walloca	\
-Wctor-dtor-privacy -Wduplicated-cond -Wduplicated-branches		\
-Werror -Wextra -Wfatal-errors -Winit-self -Wlogical-op			\
-Wold-style-cast -Wpedantic -Wshadow -Wunused-const-variable=1	\
-Wzero-as-null-pointer-constant
CXXFLAGS=-Wall $$opts

assignment=HW3

%.o: %.cpp
	g++ -c $(CXXFLAGS) $<

$(assignment).a: double_vector.o 
	ar -rcs $@ $^
		
test: $(assignment).a
	g++ -o test.exe test.cpp $<

# do i need make app?
app: $(assignment).a
	g++ $(CXXFLAGS) -o $(assignment) app.cpp $<

tar:
	tar -cf $(assignment).tar *.cpp Makefile *.h 

clean:
	rm -f $(assignment) $(assignment).tar *.o *.gch *.gcov a.out *.a *.exe