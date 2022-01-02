.PHONY: test
test:
	@g++ -Isrc -Itest -fpermissive -o test/test src/FPGAwire.cpp src/FPGAreg.cpp src/FPGAgates.cpp test/*.c test/*.cpp
	@test/test