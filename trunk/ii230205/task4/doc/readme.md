<p align="center"> Министерство образования Республики Беларусь</p>
<p align="center">Учреждение образования</p>
<p align="center">“Брестский Государственный технический университет”</p>
<p align="center">Кафедра ИИТ</p>
<br><br><br><br><br><br><br>
<p align="center">Лабораторная работа №4</p>
<p align="center">По дисциплине “Общая теория интеллектуальных систем”</p>
<p align="center">Тема: “Работа с проектом "NIKA" (Intelligent Knowledge-driven Assistant)”</p>
<br><br><br><br><br>
<p align="right">Выполнила:</p>
<p align="right">Студент 2 курса</p>
<p align="right">Группы ИИ-26</p>
<p align="right">Сугак В.А.</p>
<p align="right">Проверил:</p>
<p align="right">Ситковец Я.С.</p>
<br><br><br><br><br>
<p align="center">Брест 2024</p>

<hr>

# Общее задание #
1.Изучить руководство.

2.Запустить данный проект на локальной машине (домашний персональный компьютер, ноутбук, рабочая машина в аудитории и т.п.). Продемонстрировать работу проекта преподавателю.

3.Написать отчет по выполненной работе в .md формате (readme.md) и с помощью pull request разместить его в следующем каталоге: trunk\ii0xxyy\task_04\doc.

<hr>

# Выполнение задания #

Для выполнения этой лабораторной работы нам понадобилось установить Docker, а замем установить проект "NIKA". После установки и запуска проекта, мне нужно было его протестировать. В ходе выполнения работы я сделала несколько снимков, которые отражают работоспособность данного проекта.

Installation:
git clone -c core.longpaths=true -c core.autocrlf=true https://github.com/ostis-apps/nika
cd nika
git submodule update --init --recursive
docker compose pull

Запуск:
docker compose up --no-build

Данная команда запускает 2 веб-интерфейса:
sc-web - localhost:8000
dialogue web UI - localhost:3033

Снимки sc-web:
img6.png
img5.png

Интерфейс web-диалога:
img1.png
img2.png
img3.png
img4.png

'''