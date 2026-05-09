#include "content.h"
#include <string.h>

const char *main_themes[] = {
    "Базис",
    "Указатели",
    "Функции"
};


const char *base_themes[] = {
    "Переменные",
    "Операторы",
    NULL
};

const char *pointers_themes[] = {
    "Адресация",
    "Динамическая память",
    NULL
};

const char *funcs_themes[] = {
    "Объявление и вызов",
    "Рекурсия",
    NULL
};


const char *ui_themes[] = {
    "Первое окно",
    "Виджеты и Контейнеры",
    "Сигналы и События",
    "Libadwaita и Стили",
    NULL
};


const char *c_base_code[] = {
    "#include <stdio.h>\n\nint main() {\n\t// Целое число\n\tint age = 25;\n\t// Число с плавающей точкой (дробное)\n\tfloat pi = 3.14159;\n\t// Один символ\n\tchar grade = 'A';\n\t// Строка (массив символов)\n\tchar name[] = \"C-Programmer\";\n\tprintf(\"Имя: %s\n\", name);\n\tprintf(\"Возраст: %d лет\n\", age);\n\tprintf(\"Число Пи: %.2f\n\", pi);\n\tprintf(\"Оценка: %c\n\", grade);\n\treturn 0;\n}",

    "#include <stdio.h>\n#include <stdbool.h>\n\nint main() {\n\tint a = 10, b = 3;\n\t\n\t// Арифметические операторы\n\tprintf(\"Сложение: %d + %d = %d\n\", a, b, a + b);\n\tprintf(\"Остаток от деления: %d %% %d = %d\n\", a, b, a % b);\n\t\n\t// Операторы сравнения и логики\n\tbool result = (a > b) && (b > 0); // Истина, если a > b И b > 0\n\t\n\tif (result) {\n\t\tprintf(\"Оба условия верны!\n\");\n\t} else {\n\t\tprintf(\"Одно из условий ложно\n\");\n\t}\n\n\t// Инкремент\n\ta++; \n\tprintf(\"Значение a после a++: %d\n\", a);\n\n\treturn 0;\n}",

    "#include <stdio.h>\n\nint main() {\n\tint number = 42;\n\tint *ptr = &number; // ptr хранит адрес переменной number\n\n\tprintf(\"Значение переменной: %d\n\", number);\n\tprintf(\"Адрес переменной (&number): %p\n\", (void*)&number);\n\tprintf(\"Значение указателя (ptr): %p\n\", (void*)ptr);\n\t\n\t// Разыменование: получаем значение по адресу, который хранит ptr\n\tprintf(\"Значение по адресу в ptr (*ptr): %d\n\", *ptr);\n\n\t// Изменение значения через указатель\n\t*ptr = 100;\n\tprintf(\"Новое значение number через указатель: %d\n\", number);\n\n\treturn 0;\n}",

    "#include <stdio.h>\n#include <stdlib.h>\n\nint main() {\n\tint n;\n\tprintf(\"Введите размер массива: \");\n\tif (scanf(\"%d\", &n) != 1) return 1;\n\n\t// Выделение памяти под массив из n целых чисел\n\tint *array = (int *)malloc(n * sizeof(int));\n\n\tif (array == NULL) {\n\t\tprintf(\"Ошибка выделения памяти!\n\");\n\t\treturn 1;\n\t}\n\n\t// Заполнение массива\n\tfor (int i = 0; i < n; i++) {\n\t\tarray[i] = i * 10;\n\t}\n\n\tprintf(\"Динамический массив: \");\n\tfor (int i = 0; i < n; i++) {\n\t\tprintf(\"%d \", array[i]);\n\t}\n\tprintf(\"\n\");\n\n\t// ОБЯЗАТЕЛЬНО освобождаем память\n\tfree(array);\n\tprintf(\"Память освобождена.\n\");\n\n\treturn 0;\n}",

    "#include <stdio.h>\n\n// Прототип функции (объявление)\nint multiply(int x, int y);\n\nint main() {\n\tint a = 5, b = 6;\n\t\n\t// Вызов функции\n\tint result = multiply(a, b);\n\t\n\tprintf(\"Результат умножения %d на %d равен %d\n\", a, b, result);\n\t\n\treturn 0;\n}\n\n// Реализация функции\nint multiply(int x, int y) {\n\treturn x * y;\n}",

    "#include <stdio.h>\n\n// Функция для вычисления факториала числа n (n!)\nunsigned long long factorial(int n) {\n\t// Базовый случай: если n равно 0 или 1, факториал равен 1\n\tif (n <= 1) {\n\t\treturn 1;\n\t}\n\t// Рекурсивный шаг: n! = n * (n-1)!\n\treturn n * factorial(n - 1);\n}\n\nint main() {\n\tint num = 5;\n\tprintf(\"Факториал числа %d равен %llu\n\", num, factorial(num));\n\t\n\t// Пример с числом 10\n\tprintf(\"Факториал числа 10 равен %llu\n\", factorial(10));\n\t\n\treturn 0;\n}"
};

const char *gtk4_code[] = {
    "#include <gtk/gtk.h>\n\nstatic void activate(GtkApplication *app, gpointer user_data) {\n\t// Создаем окно\n\tGtkWidget *window = gtk_application_window_new(app);\n\tgtk_window_set_title(GTK_WINDOW(window), \"Привет, GTK4!\");\n\tgtk_window_set_default_size(GTK_WINDOW(window), 400, 300);\n\n\t// Создаем простую надпись\n\tGtkWidget *label = gtk_label_new(\"Это мое первое окно на GTK4!\");\n\tgtk_window_set_child(GTK_WINDOW(window), label);\n\n\tgtk_window_present(GTK_WINDOW(window));\n}\n\nint main(int argc, char **argv) {\n\tGtkApplication *app = gtk_application_new(\"com.example.firstwindow\", G_APPLICATION_DEFAULT_FLAGS);\n\tg_signal_connect(app, \"activate\", G_CALLBACK(activate), NULL);\n\t\n\tint status = g_application_run(G_APPLICATION(app), argc, argv);\n\tg_object_unref(app);\n\t\n\treturn status;\n}",

    "#include <gtk/gtk.h>\n\nstatic void activate(GtkApplication *app, gpointer user_data) {\n\tGtkWidget *window = gtk_application_window_new(app);\n\tgtk_window_set_title(GTK_WINDOW(window), \"Виджеты и Контейнеры\");\n\tgtk_window_set_default_size(GTK_WINDOW(window), 300, 200);\n\n\t// Создаем вертикальный контейнер (основной)\n\tGtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);\n\tgtk_widget_set_margin_all(vbox, 20);\n\tgtk_window_set_child(GTK_WINDOW(window), vbox);\n\n\t// Добавляем надпись\n\tGtkWidget *label = gtk_label_new(\"Выберите действие:\");\n\tgtk_box_append(GTK_BOX(vbox), label);\n\n\t// Создаем горизонтальный контейнер для кнопок\n\tGtkWidget *hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);\n\tgtk_box_append(GTK_BOX(vbox), hbox);\n\n\t// Добавляем кнопки в горизонтальный ряд\n\tGtkWidget *btn1 = gtk_button_new_with_label(\"ОК\");\n\tGtkWidget *btn2 = gtk_button_new_with_label(\"Отмена\");\n\t\n\tgtk_box_append(GTK_BOX(hbox), btn1);\n\tgtk_box_append(GTK_BOX(hbox), btn2);\n\n\tgtk_window_present(GTK_WINDOW(window));\n}\n\nint main(int argc, char **argv) {\n\tGtkApplication *app = gtk_application_new(\"com.example.widgets\", G_APPLICATION_DEFAULT_FLAGS);\n\tg_signal_connect(app, \"activate\", G_CALLBACK(activate), NULL);\n\treturn g_application_run(G_APPLICATION(app), argc, argv);\n}",

    "#include <gtk/gtk.h>\n\n// Структура для передачи нескольких виджетов в функцию-обработчик\ntypedef struct {\n\tGtkWidget *label;\n\tint count;\n} AppData;\n\nstatic void on_button_clicked(GtkButton *btn, gpointer user_data) {\n\tAppData *data = (AppData *)user_data;\n\tdata->count++;\n\t\n\tchar buffer[50];\n\tsnprintf(buffer, sizeof(buffer), \"Кнопка нажата %d раз!\", data->count);\n\tgtk_label_set_text(GTK_LABEL(data->label), buffer);\n}\n\nstatic void activate(GtkApplication *app, gpointer user_data) {\n\tGtkWidget *window = gtk_application_window_new(app);\n\tgtk_window_set_title(GTK_WINDOW(window), \"Сигналы и События\");\n\tgtk_window_set_default_size(GTK_WINDOW(window), 300, 150);\n\n\tGtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 15);\n\tgtk_widget_set_margin_all(box, 20);\n\tgtk_window_set_child(GTK_WINDOW(window), box);\n\n\t// Данные для обработчика\n\tAppData *data = g_new(AppData, 1);\n\tdata->count = 0;\n\n\tdata->label = gtk_label_new(\"Нажми на кнопку!\");\n\tgtk_box_append(GTK_BOX(box), data->label);\n\n\tGtkWidget *button = gtk_button_new_with_label(\"Нажми меня\");\n\t// Подключаем сигнал \"clicked\" к нашей функции\n\tg_signal_connect(button, \"clicked\", G_CALLBACK(on_button_clicked), data);\n\tgtk_box_append(GTK_BOX(box), button);\n\n\tgtk_window_present(GTK_WINDOW(window));\n}\n\nint main(int argc, char **argv) {\n\tGtkApplication *app = gtk_application_new(\"com.example.signals\", G_APPLICATION_DEFAULT_FLAGS);\n\tg_signal_connect(app, \"activate\", G_CALLBACK(activate), NULL);\n\treturn g_application_run(G_APPLICATION(app), argc, argv);\n}",

    "#include <adwaita.h>\n\nstatic void activate(AdwApplication *app, gpointer user_data) {\n\t// Используем AdwApplicationWindow вместо GtkApplicationWindow\n\tGtkWidget *window = adw_application_window_new(app);\n\tgtk_window_set_title(GTK_WINDOW(window), \"Современный GTK4\");\n\tgtk_window_set_default_size(GTK_WINDOW(window), 400, 300);\n\n\t// Создаем современный заголовок окна (HeaderBar)\n\tGtkWidget *header = adw_header_bar_new();\n\t\n\t// Создаем основной контент\n\tGtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);\n\t\n\t// Добавляем заголовок в начало\n\tgtk_box_append(GTK_BOX(box), header);\n\t\n\t// Добавляем красивую карточку (AdwClamp помогает центрировать контент)\n\tGtkWidget *clamp = adw_clamp_new();\n\tgtk_box_append(GTK_BOX(box), clamp);\n\n\tGtkWidget *card = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);\n\tgtk_widget_set_margin_all(card, 20);\n\tgtk_widget_add_css_class(card, \"card\"); // Стандартный класс Adwaita\n\t\n\tGtkWidget *label = gtk_label_new(\"Это окно создано с помощью Libadwaita!\");\n\tgtk_box_append(GTK_BOX(card), label);\n\t\n\tgtk_box_append(GTK_BOX(GTK_BOX(clamp)), card);\n\n\tgtk_window_set_child(GTK_WINDOW(window), box);\n\tgtk_window_present(GTK_WINDOW(window));\n}\n\nint main(int argc, char **argv) {\n\t// Используем AdwApplication\n\tAdwApplication *app = adw_application_new(\"com.example.adwaita\", G_APPLICATION_DEFAULT_FLAGS);\n\tg_signal_connect(app, \"activate\", G_CALLBACK(activate), NULL);\n\t\n\tint status = g_application_run(G_APPLICATION(app), argc, argv);\n\tg_object_unref(app);\n\t\n\treturn status;\n}"
};


const char** get_theme_list(const char *theme_name) {
    if (strcmp("Базовый C", theme_name) == 0) {
        return main_themes;
    }
    else if(strcmp("GTK 4", theme_name) == 0) {
        return ui_themes;
    }
    else if(strcmp("Базис", theme_name) == 0) {
        return base_themes;
    }
    else if(strcmp("Указатели", theme_name) == 0) {
        return pointers_themes;
    }
    else if(strcmp("Функции", theme_name) == 0) {
        return funcs_themes;
    }
    else {
        return nullptr;
    }
}

const char* get_source_code(const char *theme_name) {
    if (strcmp("Переменные", theme_name) == 0) {
        return c_base_code[0];
    }
    else if(strcmp("Операторы", theme_name) == 0) {
        return c_base_code[1];
    }
    else if(strcmp("Адресация", theme_name) == 0) {
        return c_base_code[2];
    }
    else if(strcmp("Динамическая память", theme_name) == 0) {
        return c_base_code[3];
    }
    else if(strcmp("Объявление и вызов", theme_name) == 0) {
        return c_base_code[4];
    }
    else if(strcmp("Рекурсия", theme_name) == 0) {
        return c_base_code[5];
    }
    else if(strcmp("Первое окно", theme_name) == 0) {
        return gtk4_code[0];
    }
    else if(strcmp("Виджеты и Контейнеры", theme_name) == 0) {
        return gtk4_code[1];
    }else if(strcmp("Сигналы и События", theme_name) == 0) {
        return gtk4_code[2];
    }
    /* else if(strcmp("Libadwaita и Стили", theme_name) == 0) {
        return gtk4_code[3];
    } */
    else {
        return nullptr;
    }
}