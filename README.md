# Template Render

### Download and Open

Download as a zip archive or clone the repository:

```
git clone https://github.com/lnupmi11/template-render.git
```
Move to the project folder and use `TemplateRender.sln` for opening
the project in Microsoft Visual Studio.

### Usage

1. Comment on `TEST_CASE()` line in `AppStart.cpp`.
2. Specify the path `TEMPLATE_DIR` for template search and `ENDPOINT_DIR` for rendered HTML document in `Constants.h` file.
(Default: `TEMPLATE_DIR = "Tests/Templates/"`, `ENDPOINT_DIR = "Tests/"` )
3. Create context object using vector of pairs of keys and values (or do not create if you do not use it).
    > \* For custom classes and structures it is necessary to overload `std::ostringstream` operator.
4. Design your template.
5. In `AppStart.cpp` call `TemplateRender::render()` function and pass arguments:
the first is template name, the second is rendered HTML document name, the third is your context
(if you do not use context ignore this argument, default is `nullptr`).
6. Build and run the project using Microsoft Visual Studio tools.
7. Find rendered HTML document in the directory that you specified.  

### Available syntax
1. 'For' loop statement tag, example:
    
    ```
        {% for (size_t i = 0; i < 5; i++) %}
            /*loop_body*/
            {{ i }}
            /*loop_body*/
        {% endfor %}
    ```
2. 'If' statement tag, example:

    ```
        {% if (some_var_from_context) %}
            /*condition_body*/
        {% else %}
            /*else_body*/
        {% endif %}
    ```
    ```
        {% if (first_var_from_context <= second_var_from_context) %}
            /*condition_body*/
        {% endif %}
    ```
3. Tag for including another html documents, example:

    ```
        {% #include "some_snippet.html" %}
    ```
4. Tag for commenting code in templates, example:

    ```
        {% comment "Comment explanation" %}
            /*Some content to comment on*/
        {% endcomment %}
    ```
    
5. Variables, example:

    ```
        {{ some_var_from_context }}
    ```

### Authors

* **[Yuriy Vasko](https://github.com/YuraVasko)**
* **[Olya Pastushchak](https://github.com/OlyaPastushchak)**
* **[Yuriy Lisovskiy](https://github.com/YuriyLisovskiy)**
* **[Natalia Pachva](https://github.com/nataliapachva)**
* **[Andriy Dubyk](https://github.com/andrewDubyk)**
* **[Andrii Vaskiv](https://github.com/AndriiVaskiv)**
* **[Oleg Zhuk](https://github.com/NSArray47)**
