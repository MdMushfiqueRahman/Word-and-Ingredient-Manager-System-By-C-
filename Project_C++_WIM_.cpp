/****************************************
*
* Student Name: Md Mushfique Rahman
* Date Due: 5/1/2024
* Date Submitted: 5/1/2024
* Program Name: Application Tool (WiM) 
* Program Description: WIM is a comprehensive tool designed to streamline word frequency analysis and ingredient management tasks. It offers an intuitive interface for analyzing the frequency of words in a text file, including features to preprocess text, count word occurrences, and present results in a clear table format. Additionally, WIM provides robust functionality for managing a list of ingredients, allowing users to easily add, remove, edit, search, and display ingredients. With features for saving ingredient lists and checking recipe compatibility, WIM empowers users to efficiently organize both textual data and culinary essentials.
*
*
****************************************/
                              #include <iostream>
                              #include <fstream>
                              #include <sstream>
                              #include <vector>
                              #include <map>
                              #include <algorithm>
                              #include <cctype>
                              #include <iomanip>

                              // Word Count Program
                              void wordFrequencyAnalysis(const std::string& file_name) {
                                  std::ifstream file(file_name);
                                  if (!file.is_open()) {
                                      std::cerr << "Error opening file: " << file_name << std::endl;
                                      return;
                                  }

                                  std::vector<std::string> words;
                                  std::map<std::string, int> word_frequency;

                                  std::string word;
                                  while (file >> word) {
                                      word.erase(std::remove_if(word.begin(), word.end(), ::ispunct), word.end());
                                      std::transform(word.begin(), word.end(), word.begin(), ::tolower);
                                      auto it = std::find(words.begin(), words.end(), word);
                                      if (it == words.end()) {
                                          words.push_back(word);
                                          word_frequency[word] = 1;
                                      } else {
                                          word_frequency[word]++;
                                      }
                                  }

                                  std::cout << "Word Frequency Analysis" << std::endl;
                                  std::cout << std::setw(15) << "Word" << std::setw(10) << "Frequency" << std::endl;
                                  for (const auto& pair : word_frequency) {
                                      std::cout << std::setw(15) << pair.first << std::setw(10) << pair.second << std::endl;
                                  }
                              }

                              // Cook Ingredient Manager Program
                              struct IngredientManager {
                                  std::vector<std::string> ingredients_list;

                                  void loadIngredients(const std::string& file_name) {
                                      std::ifstream file(file_name);
                                      if (!file.is_open()) {
                                          std::cerr << "Error opening file: " << file_name << std::endl;
                                          return;
                                      }

                                      std::string ingredient;
                                      while (std::getline(file, ingredient)) {
                                          ingredients_list.push_back(ingredient);
                                      }
                                  }

                                  void addIngredient(const std::string& ingredient) {
                                      ingredients_list.push_back(ingredient);
                                  }

                                  void removeIngredient(const std::string& ingredient) {
                                      ingredients_list.erase(std::remove(ingredients_list.begin(), ingredients_list.end(), ingredient), ingredients_list.end());
                                  }

                                  bool searchIngredient(const std::string& ingredient) {
                                      return std::find(ingredients_list.begin(), ingredients_list.end(), ingredient) != ingredients_list.end();
                                  }

                                  void editIngredient(const std::string& oldIngredient, const std::string& newIngredient) {
                                      auto it = std::find(ingredients_list.begin(), ingredients_list.end(), oldIngredient);
                                      if (it != ingredients_list.end()) {
                                          *it = newIngredient;
                                      }
                                  }

                                  void saveToFile(const std::string& file_name) {
                                      std::ofstream file(file_name);
                                      if (!file.is_open()) {
                                          std::cerr << "Error opening file: " << file_name << std::endl;
                                          return;
                                      }

                                      for (const auto& ingredient : ingredients_list) {
                                          file << ingredient << std::endl;
                                      }
                                  }

                                  void displayIngredients() {
                                      for (const auto& ingredient : ingredients_list) {
                                          std::cout << ingredient << std::endl;
                                      }
                                  }

                                  void checkRecipe(const std::string& recipe_file_name) {
                                      std::ifstream file(recipe_file_name);
                                      if (!file.is_open()) {
                                          std::cerr << "Error opening file: " << recipe_file_name << std::endl;
                                          return;
                                      }

                                      std::vector<std::string> recipe_ingredients;
                                      std::string line;
                                      while (std::getline(file, line)) {
                                          std::istringstream iss(line);
                                          std::string word;
                                          while (iss >> word) {
                                              if (word.front() == '<' && word.back() == '>') {
                                                  recipe_ingredients.push_back(word.substr(1, word.size() - 2));
                                              }
                                          }
                                      }

                                      std::cout << "Ingredients not found in pantry:" << std::endl;
                                      for (const auto& ingredient : recipe_ingredients) {
                                          if (!searchIngredient(ingredient)) {
                                              std::cout << ingredient << std::endl;
                                          }
                                      }
                                  }
                              };

                              int main() {
                                  int choice;
                                  std::string quote_file_name = "quote.txt"; // Your quote file here
                                  IngredientManager manager;
                                  manager.loadIngredients("pantry.txt"); // Load pantry ingredients

                                  do {
                                      std::cout << "--- Main Menu ---" << std::endl;
                                      std::cout << "1. Word Frequency Analysis" << std::endl;
                                      std::cout << "2. Ingredient Manager" << std::endl;
                                      std::cout << "3. Exit" << std::endl;
                                      std::cout << "Enter your choice: ";
                                      std::cin >> choice;
                                      std::cin.ignore(); // Clear input buffer

                                      switch (choice) {
                                          case 1:
                                              wordFrequencyAnalysis(quote_file_name);
                                              break;
                                          case 2: {
                                              int ingredient_choice;
                                              std::string ingredient, new_ingredient, recipe_file_name;

                                              do {
                                                  std::cout << "--- Ingredient Manager Menu ---" << std::endl;
                                                  std::cout << "1. Add ingredient" << std::endl;
                                                  std::cout << "2. Remove ingredient" << std::endl;
                                                  std::cout << "3. Search for ingredient" << std::endl;
                                                  std::cout << "4. Edit ingredient" << std::endl;
                                                  std::cout << "5. Save ingredients to File" << std::endl;
                                                  std::cout << "6. Display ingredients" << std::endl;
                                                  std::cout << "7. Check Recipe for ingredients" << std::endl;
                                                  std::cout << "8. Exit" << std::endl;
                                                  std::cout << "Enter your choice: ";
                                                  std::cin >> ingredient_choice;
                                                  std::cin.ignore(); // Clear input buffer

                                                  switch (ingredient_choice) {
                                                      case 1:
                                                          std::cout << "Enter ingredient to add: ";
                                                          std::getline(std::cin, ingredient);
                                                          manager.addIngredient(ingredient);
                                                          break;
                                                      case 2:
                                                          std::cout << "Enter ingredient to remove: ";
                                                          std::getline(std::cin, ingredient);
                                                          manager.removeIngredient(ingredient);
                                                          break;
                                                      case 3:
                                                          std::cout << "Enter ingredient to search: ";
                                                          std::getline(std::cin, ingredient);
                                                          std::cout << (manager.searchIngredient(ingredient) ? "Found" : "Not found") << std::endl;
                                                          break;
                                                      case 4:
                                                          std::cout << "Enter ingredient to edit: ";
                                                          std::getline(std::cin, ingredient);
                                                          std::cout << "Enter new ingredient name: ";
                                                          std::getline(std::cin, new_ingredient);
                                                          manager.editIngredient(ingredient, new_ingredient);
                                                          break;
                                                      case 5:
                                                          manager.saveToFile("pantry.txt");
                                                          break;
                                                      case 6:
                                                          manager.displayIngredients();
                                                          break;
                                                      case 7:
                                                          std::cout << "Enter recipe filename: ";
                                                          std::getline(std::cin, recipe_file_name);
                                                          manager.checkRecipe(recipe_file_name);
                                                          break;
                                                      case 8:
                                                          break;
                                                      default:
                                                          std::cout << "Invalid choice. Please try again." << std::endl;
                                                  }
                                              } while (ingredient_choice != 8);
                                              break;
                                          }
                                          case 3:
                                              break;
                                          default:
                                              std::cout << "Invalid choice. Please try again." << std::endl;
                                      }
                                  } while (choice != 3);

                                  return 0;
                              }
