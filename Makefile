CXX      := g++
CXXFLAGS := -O2 -std=c++17 -Wall -Wextra
BIN      := bin
ALGOS    := global local semiglobal
RUN      := $(addprefix run-,$(ALGOS))

.PHONY: all test clean $(RUN)

all: $(addprefix $(BIN)/,$(ALGOS))

$(BIN)/%: src/alignment/%.cpp | $(BIN)
	$(CXX) $(CXXFLAGS) $< -o $@

$(BIN):
	mkdir -p $(BIN)

test: all
	@bash tests/run.sh

$(RUN): run-%: $(BIN)/%
	@./$(BIN)/$* < tests/$*.in

clean:
	rm -rf $(BIN)
