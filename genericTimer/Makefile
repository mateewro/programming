all:
	@echo 'Build and test genericTimer'
	@[ -d build ] || ( mkdir build )
	@cd build && cmake .. && make; ./test/genericTimer
clean:
	@rm -rf build
rebuild: clean all

