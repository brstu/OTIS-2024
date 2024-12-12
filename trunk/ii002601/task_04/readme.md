<p align="center"> ������������ ����������� ���������� ��������</p>
<p align="center">���������� �����������</p>
<p align="center">���������� ��������������� ����������� �����������</p>
<p align="center">������� ���</p>
<br><br><br><br><br><br><br>
<p align="center">������������ ������ �4</p>
<p align="center">�� ���������� ������ ������ ���������������� ������</p>
<p align="center">����: ������� � �������� "NIKA" (Intelligent Knowledge-driven Assistant)�</p>
<br><br><br><br><br>
<p align="right">��������:</p>
<p align="right">������� 2 �����</p>
<p align="right">������ ��-26</p>
<p align="right">����� �.�.</p>
<p align="right">���������:</p>
<p align="right">�������� �. �.</p>
<br><br><br><br><br>
<p align="center">����� 2023</p>

---

# ����� ������� #
1. ������� [�����������](https://github.com/ostis-apps/nika).

2. ��������� ������ ������ �� ��������� ������ (�������� ������������ ���������, �������, ������� ������ � ��������� � �.�.). ������������������ ������ ������� �������������.

3. �������� ����� �� ����������� ������ � .md ������� (readme.md) � � ������� pull request ���������� ��� � ��������� ��������: trunk\ii0xxyy\task_04\doc.


---

# ��������� #

```
git clone -c core.longpaths=true -c core.autocrlf=true https://github.com/ostis-apps/nika
cd nika
git submodule update --init --recursive
docker compose pull
```
����� ���������� ������������� ���������� [Docker](https://docs.docker.com/)(c �������� Compose)
 
# ������ #
```
docker compose up --no-build
```
��� ������� �������� ��� ���-����������:

sc-web - ```localhost:8000```

dialogue web UI - ```localhost:3033```

# ��������� #

sc-web - ```localhost:8000```:
![���������:](./nika_1.png)


dialogue web UI - ```localhost:3033```:
![���������:](./nika_2.png)
![���������:](./nika_3.png)


Docker Desktop:
![���������:](./nika_4.png)