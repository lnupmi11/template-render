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
2. In `Constants.h` file specify the paths `TEMPLATE_DIR` for template search, `ENDPOINT_DIR` for rendered HTML document 
and `MEDIA_DIR` for media files search.
(Default: `TEMPLATE_DIR = "Tests/Templates/"`, `ENDPOINT_DIR = "Tests/"`, `MEDIA_DIR = "Media/"`)
3. Create context object using vector of pairs of keys and values (or do not create if you do not use it).
    > \* Operator `std::ostringstream` is required for custom classes and structures.
4. Design your template (check for 'Available syntax' section).
5. In `AppStart.cpp` call `TemplateRender::render()` function and pass arguments:
the first is template name, the second is rendered HTML document name, the third is your context
(if you do not use context ignore this argument, default is `nullptr`).
6. Build and run the project using Microsoft Visual Studio tools.
7. Find rendered HTML document in the directory that you specified.  

### Available syntax
1. 'For' loop statement tag.

    Example:
    
    ```
        {% for (size_t i = 0; i < 5; i++) %}
            /*loop_body*/
            {{ i }}
            /*loop_body*/
        {% endfor %}
    ```
2. 'If' statement tag.

    Example:

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
    > \* Only a comparison of two strings or two numbers is available.
3. Tag for including another html documents.

    Example:

    ```
        {% #include "some_snippet.html" %}
    ```
4. Tag for commenting code in templates.

    Example:

    ```
        {% comment "Comment explanation" %}
            /*Some content to comment on*/
        {% endcomment %}
    ```
    
5. Variables.

    Example:

    ```
        {{ some_var_from_context }}
    ```
6. Images.

    Example:

    ```
        <img src="{% #image 'some_image_from_context' %}" />
    ```
    ```
        <img src="{% #image 'some_image.png' %}" />
    ```

### Authors

* **[Yuriy Vasko](https://github.com/YuraVasko)**
* **[Olya Pastushchak](https://github.com/OlyaPastushchak)**
* **[Yuriy Lisovskiy](https://github.com/YuriyLisovskiy)**
* **[Natalia Pachva](https://github.com/nataliapachva)**
* **[Andriy Dubyk](https://github.com/andrewDubyk)**
* **[Andrii Vaskiv](https://github.com/AndriiVaskiv)**
* **[Oleg Zhuk](https://github.com/NSArray47)**
