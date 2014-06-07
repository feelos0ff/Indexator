Сборка
изменить файл objects.mk:
в USER_OBJS прописать полный путь до собранной стемки (libstemka.a) 
при необходимости изменения путей до либов postgresql: 
в makefile изменить строку g++ -L/opt/PostgreSQL/9.3/lib -o "index" $(OBJS) $(USER_OBJS) $(LIBS) на необходимую
в файле Release/src/cpp/subdir.mk добавить подключение загаловочников
сделать make в папке release
