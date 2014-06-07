<h2>Сборка </h2>
<h4> Зависимости</h4>
<h8>g++ python-psycopg2 postgresql-9.3 libpq-dev<br>
Наличие локали 1251 sudo locale-gen ru_RU.CP1251
</h8>
<h4> Собственно как собрать </h4>
<h8>изменить параметры сборки
сделать make в папке release</h8>
<h4>Изменения в сборке</h4>
<h8>в файле objects.mk в USER_OBJS прописать полный путь до собранной стемки (libstemka.a) </h8>
<h4>при необходимости изменения путей до либов postgresql: </h4>
<h8>
в makefile изменить строку g++ -L/opt/PostgreSQL/9.3/lib -o "index" $(OBJS) $(USER_OBJS) $(LIBS) на необходимую<br>
в файле Release/src/cpp/subdir.mk добавить подключение загаловочников
</h8>
<h2>Изменение проекта</h2>
<h4>Добавление ранжирования</h4>
<h8>Реализация ранжирования должна нахдиться в файлах ranking.h и ranking.cpp<br>
вызывается методом CuttingList из Query<br>
<h4>Для тестирования</h4>
<h8>Выборку указать в main.cpp в idx.CreateIndex(98, 101) <br>
Если 2й пврвметр 0, то выборка до конца данных<br>
Создать объект Query в main.cpp<br>
вызвать  SetTable() с аргументом указатель на IndexTable    <br>
далее работать через ExecQuery(), передавая составной или атомарный запрос
<h4>Для ускорения</h4>
<h8>Для ускорения проекта возможно увеличить количество файлов в максимальном наборе<br>
В файле index.h в конструкторе класса Index увеличить _maxCountOfText

</h8>
<h2>Запуск</h2>
<h8> запуск осуществляется ./index
перед повторным запуском необходимо сделать rm *dict *idx *stat
начнётся повторная переиндексация
данные на вход принимаются в кодировке cp1251, поэтому следует проверить кодировку консоли
</h8>

<h2>Возможны баги </h2>

