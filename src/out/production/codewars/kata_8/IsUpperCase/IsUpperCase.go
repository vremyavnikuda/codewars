// Package IsUpperCase
// Является ли строка прописной?
package IsUpperCase

type MyString string

func (s MyString) IsUpperCase() bool {
	//цикл со всеми символами строки s
	for _, char := range s {
		//если символ находится в диапазоне между 'a'и'z'(включительно)
		if char >= 'a' && char <= 'z' {
			//то это означает ,что строка содержит маленькие буквы
			return false
		}
	}
	//Если цикл завершился, значит строка не содержит маленькие буквы
	//поэтому функция возвращает true
	return true
}
