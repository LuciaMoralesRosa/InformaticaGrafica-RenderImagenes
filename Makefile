# Compilador y flags
CXX := g++
CXXFLAGS := -std=c++17 -Wall -Iinclude -Isrc -Itests
LDFLAGS := 

# Carpetas
SRC_DIR := src
BUILD_DIR := build
TEST_DIR := tests

# Encuentra todos los .cpp del src
SRC_FILES := $(wildcard $(SRC_DIR)/**/**/*.cpp) $(wildcard $(SRC_DIR)/**/*.cpp) $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRC_FILES))

# Encuentra todos los .cpp del tests
TEST_FILES := $(wildcard $(TEST_DIR)/**/*.cpp) $(wildcard $(TEST_DIR)/*.cpp)
OBJ_TEST_FILES := $(patsubst $(TEST_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(TEST_FILES))

# Archivos para main y tests
MAIN_OBJ := $(BUILD_DIR)/main.o
TEST_OBJ := $(BUILD_DIR)/test.o

# Ejecutables
MAIN_EXE := main.exe
TEST_EXE := test.exe

# Regla por defecto: compilar main
all: $(MAIN_EXE)

# Ejecutable principal
$(MAIN_EXE): $(MAIN_OBJ) $(OBJ_FILES)
	$(CXX) $^ -o $@ $(LDFLAGS)

# Ejecutable de tests
tests: $(TEST_EXE)

$(TEST_EXE): $(TEST_OBJ) $(OBJ_FILES) $(OBJ_TEST_FILES)
	$(CXX) $^ -o $@ $(LDFLAGS)


# Función para arreglar rutas tipo Unix en mkdir de Windows
fix_path = $(subst /,\,$1)

# Compilar main.cpp
$(BUILD_DIR)/main.o: main.cpp
	@if not exist "$(call fix_path,$(BUILD_DIR))" mkdir $(call fix_path,$(BUILD_DIR))
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compilar test.cpp
$(BUILD_DIR)/test.o: $(TEST_DIR)/test.cpp
	@if not exist "$(call fix_path,$(BUILD_DIR))" mkdir $(call fix_path,$(BUILD_DIR))
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compilar todos los .cpp en src/
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@if not exist "$(call fix_path,$(dir $@))" mkdir $(call fix_path,$(dir $@))
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compilar todos los .cpp en tests/
$(BUILD_DIR)/%.o: $(TEST_DIR)/%.cpp
	@if not exist "$(call fix_path,$(dir $@))" mkdir $(call fix_path,$(dir $@))
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpieza
clean:
	@echo Eliminando archivos de compilación...
	@if exist $(BUILD_DIR) rmdir /s /q $(BUILD_DIR)
	@if exist main.exe del /q main.exe
	@if exist test.exe del /q test.exe

.PHONY: all tests clean
