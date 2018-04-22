ALL: src/main.cpp src/Metabolite.cpp src/Rxn.cpp
	g++ -std=gnu++11 src/main.cpp src/Metabolite.cpp src/Rxn.cpp -o prog_exec

.PHONY: test
test: test/HormoneTests.cpp src/metabolite.cpp src/rxn.cpp src/load.cpp
	g++ -std=gnu++11 -Werror test/HormoneTests.cpp src/metabolite.cpp src/enzyme.cpp src/rxn.cpp src/load.cpp -o exec

clean:
	rm exec
