// Пример 1: Простейшая структура с одним lifetime
struct TextHolder<'a> {
    content: &'a str, // Эта структура "заимствует" строку на время 'a
}

impl<'a> TextHolder<'a> {
    // Конструктор принимает ссылку и возвращает структуру с тем же lifetime
    fn new(text: &'a str) -> Self {
        TextHolder { content: text }
    }

    // Метод возвращает ссылку с тем же lifetime, что и структура
    fn get_content(&self) -> &'a str {
        self.content
    }

    // Метод может принимать другие параметры с независимыми lifetime
    fn compare_with(&self, other: &str) -> bool {
        self.content == other
    }
}

fn basic_example() {
    println!("Пример 1: Основы");

    let original = "Привет, мир!"; // original живет до конца функции

    let holder = TextHolder::new(original); // holder "заимствует" original
    println!("Содержимое: {}", holder.get_content());

    // Это работает, потому что original все еще существует
    println!("Сравнение: {}", holder.compare_with("Привет, мир!"));

    // holder может существовать, пока существует original
} // здесь заканчиваются времена жизни и original, и holder

// Пример 2: Структура с несколькими независимыми lifetime
struct BookReference<'title, 'author> {
    title: &'title str,   // Название может жить своей жизнью
    author: &'author str, // Автор может жить своей жизнью
}

impl<'title, 'author> BookReference<'title, 'author> {
    fn new(title: &'title str, author: &'author str) -> Self {
        BookReference { title, author }
    }

    // Возвращаем название - lifetime 'title
    fn get_title(&self) -> &'title str {
        self.title
    }

    // Возвращаем автора - lifetime 'author
    fn get_author(&self) -> &'author str {
        self.author
    }
}

fn multiple_lifetimes_example() {
    println!("\nПример 2: Несколько независимых lifetime");

    let book_title = "1984"; // Название живет до конца функции

    {
        let author_name = "Джордж Оруэлл"; // Автор живет только в этом блоке

        let book = BookReference::new(book_title, author_name);
        println!("Книга: {} от {}", book.get_title(), book.get_author());

        // Если бы мы попытались вынести book за пределы этого блока,
        // получили бы ошибку, так как author_name перестанет существовать
    }

    // book_title все еще доступно здесь
    println!("Название все еще существует: {}", book_title);
}

// Пример 3: Constraint между lifetime - 'b: 'a
struct ConfigWithOverride<'base, 'override_: 'base> {
    base_config: &'base str,          // Базовая конфигурация (короче живет)
    override_config: &'override_ str, // Переопределения (дольше живут)
}

impl<'base, 'override_: 'base> ConfigWithOverride<'base, 'override_> {
    fn new(base: &'base str, override_val: &'override_ str) -> Self {
        ConfigWithOverride {
            base_config: base,
            override_config: override_val,
        }
    }

    // Этот метод может безопасно вернуть любую из конфигураций
    fn get_effective_config(&self, use_override: bool) -> &'base str {
        if use_override {
            // Можем вернуть override с lifetime 'base, потому что 'override_: 'base
            // То есть override живет как минимум столько же, сколько base
            self.override_config
        } else {
            self.base_config
        }
    }
}

fn lifetime_constraints_example() {
    println!("\nПример 3: Constraint между lifetime");

    let global_config = "debug=false,log_level=info"; // Живет долго

    {
        let local_override = "debug=true"; // Живет в локальном блоке

        // Это работает: 'global (long) : 'local (short)
        // global_config переживет local_override
        let config = ConfigWithOverride::new(local_override, global_config);

        println!("Базовая конфигурация: {}", config.base_config);
        println!(
            "Эффективная конфигурация: {}",
            config.get_effective_config(true)
        );
    }
}

// Пример 4: Структура, содержащая другую структуру с lifetime
struct Document<'content> {
    title: String,          // Владеет своими данными
    content: &'content str, // Заимствует контент
}

struct DocumentCollection<'docs, 'content> {
    name: String,                           // Владеет именем коллекции
    documents: &'docs [Document<'content>], // Заимствует массив документов
}

impl<'content> Document<'content> {
    fn new(title: String, content: &'content str) -> Self {
        Document { title, content }
    }

    fn preview(&self) -> &str {
        // Безопасно получаем первые 50 байт, учитывая границы UTF-8 символов
        let max_bytes = 50;

        if self.content.len() <= max_bytes {
            // Если строка короче 50 байт, возвращаем её целиком
            self.content
        } else {
            // Ищем безопасную позицию для среза, не разрезая символы
            let mut end = max_bytes;

            // Двигаемся назад до тех пор, пока не найдем границу символа
            while end > 0 && !self.content.is_char_boundary(end) {
                end -= 1;
            }

            &self.content[..end]
        }
    }
}

impl<'docs, 'content> DocumentCollection<'docs, 'content> {
    fn new(name: String, docs: &'docs [Document<'content>]) -> Self {
        DocumentCollection {
            name,
            documents: docs,
        }
    }

    fn count(&self) -> usize {
        self.documents.len()
    }

    fn get_document(&self, index: usize) -> Option<&Document<'content>> {
        self.documents.get(index)
    }
}

fn nested_structures_example() {
    println!("\nПример 4: Вложенные структуры с lifetime");

    let content1 = "Это содержимое первого документа. Оно довольно длинное.";
    let content2 = "Короткий второй документ.";

    let doc1 = Document::new("Первый документ".to_string(), content1);
    let doc2 = Document::new("Второй документ".to_string(), content2);

    let documents = vec![doc1, doc2];
    let collection = DocumentCollection::new("Моя коллекция".to_string(), &documents);

    println!(
        "Коллекция '{}' содержит {} документов",
        collection.name,
        collection.count()
    );

    if let Some(first_doc) = collection.get_document(0) {
        println!("Первый документ: '{}'", first_doc.title);
        println!("Превью: '{}'", first_doc.preview());
    }
}

// Пример 5: Методы с разными lifetime параметрами
struct TextProcessor<'data> {
    source: &'data str,
}

impl<'data> TextProcessor<'data> {
    fn new(source: &'data str) -> Self {
        TextProcessor { source }
    }

    // Метод, который работает с исходными данными
    fn get_source(&self) -> &'data str {
        self.source
    }

    // Метод с новым lifetime параметром для temporary данных
    fn process_with_temp<'temp>(&self, temp_data: &'temp str) -> (&'data str, &'temp str) {
        (self.source, temp_data)
    }

    // Метод, который возвращает строку с lifetime не длиннее исходного
    fn extract_word(&self, start: usize, end: usize) -> &'data str {
        &self.source[start..end.min(self.source.len())]
    }

    // Метод, сравнивающий с внешними данными
    fn contains_word<'word>(&self, word: &'word str) -> bool {
        self.source.contains(word)
    }
}

fn method_lifetimes_example() {
    println!("\nПример 5: Методы с разными lifetime");

    let source_text = "Rust - это системный язык программирования";
    let processor = TextProcessor::new(source_text);

    println!("Исходный текст: {}", processor.get_source());

    {
        let temp_word = "временное слово";
        let (orig, temp) = processor.process_with_temp(temp_word);
        println!("Оригинал: {}, Временное: {}", orig, temp);
    }

    let first_word = processor.extract_word(0, 4);
    println!("Первое слово: {}", first_word);

    println!("Содержит 'Rust'? {}", processor.contains_word("Rust"));
}

fn main() {
    basic_example();
    multiple_lifetimes_example();
    lifetime_constraints_example();
    nested_structures_example();
    method_lifetimes_example();
}
