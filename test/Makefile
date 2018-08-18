CXX=c++-7
CXXFLAGS=-std=c++17 -g
EXE=shader-handler-test

main:
	$(CXX) -o $(EXE) ShaderHandler.test.cpp ../ShaderHandler.cpp

.PHONY: clean
clean:
	@echo "Cleaning..."
	@rm -f $(OBJS) $(EXE)
	@rm -rf main.dSYM
	@echo "Done cleaning"

