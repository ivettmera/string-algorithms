CXX      := g++
CXXFLAGS := -O2 -std=c++17 -Wall -Wextra
BIN      := bin
ALGOS    := global local semiglobal

.PHONY: all test clean

all: $(addprefix $(BIN)/,$(ALGOS))

$(BIN)/%: src/alignment/%.cpp | $(BIN)
	$(CXX) $(CXXFLAGS) $< -o $@

$(BIN):
	mkdir -p $(BIN)

test: all
	@bash tests/run.sh

clean:
	rm -rf $(BIN)
