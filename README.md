# Template Render

### Download

```
git clone https://github.com/lnupmi11/template-render.git
```

### Usage

1. Comment on `TEST_CASE()` line.
2. Specify the path `TEMPLATE_DIR` for template search and `ENDPOINT_DIR` for rendered HTML document in `Constants.h` file.
(Default: `TEMPLATE_DIR = "Tests/"`, `ENDPOINT_DIR = "Tests/"` )
3. In `AppStart.cpp` create context object using vectors of keys and values (or do not create if you do not want to use it).
4. Design your template.
5. Call `TemplateRender::render()` function and pass parameters:
the first is template name, the second is rendered HTML document name, the third is your context
(if you do not use context ignore this parameter, default is `nullptr`).
6. Build and run the project using Microsoft Visual Visual Studio.
7. Find rendered HTML document in the directory that you specified.

### Authors

* **[Yuriy Vasko](https://github.com/YuraVasko)**
* **[Olya Pastushchak](https://github.com/OlyaPastushchak)**
* **[Yuriy Lisovskiy](https://github.com/YuriyLisovskiy)**
* **[Natalia Pachva](https://github.com/nataliapachva)**
* **[Andriy Dubyk](https://github.com/andrewDubyk)**
* **[Andrii Vaskiv](https://github.com/AndriiVaskiv)**
* **[Oleg Zhuk](https://github.com/NSArray47)**
