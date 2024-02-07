#include <iostream>
#include <pqxx/pqxx>
#include <windows.h>
#pragma execution_character_set()

// ��� �����, ������� ������ ������� ��� �������� ������������ ���������� � �������
// � ��������� ������� � ���������� �� ����� ���� �� ������
// ������� clients ������ ���������� ����� �������(��� id), ��� ���. �������, ����������� �����
// ������� telephones ������ id ������ � �����(�_ ��������(��) �������  
void create_tables_if_not_exists(pqxx::connection& c)
{
	pqxx::transaction t(c);
	t.exec("Create table if not exists clients (id int not null, first_name text not null, last_name text not null, e_mail text not null, constraint clients_pr primary key(id));" 
		"Create table if not exists telephones (id int not null, number varchar, constraint telephones_pr primary key(id), clients_id int not null references clients(id))");
	t.commit();
}

// �����, ����������� �������� ������ �������
// � ���� ������ ������ - ������-�� �������� ����� ��� ������ ������� �� ���� ������, � ������� ��� ���� ����� ������ ����.
void add_new_client(pqxx::connection& c)
{
	c.prepare("add_client", "insert into clients(id, first_name), last_name, e_mail) values($1, $2), $3, $4)");

	std::string first_name;
	std::cout << "Enter clients first name: ";
	std::getline(std::cin, first_name);

	std::string last_name;
	std::cout << "Enter clients last name: ";
	std::getline(std::cin, last_name);
	
	std::string e_mail;
	std::cout << "Enter clients e-mail: ";
	std::getline(std::cin, e_mail);

	pqxx::transaction t(c);

	t.exec_prepared("add_client", 1, first_name, last_name,e_mail);

	t.commit();
}

// �����, ����������� �������� ������� ������������� �������
// � ���� ������ ������ - ������-�� �������� ����� ��� ������ ������� �� ���� ������, � ������� ��� ���� ����� ������ ����.
void add_new_telephone_number(pqxx::connection& c)
{
	c.prepare("add_new_tel_number", "insert into telephones(id, number, clients_id) values( $1, $2, $3)");
	std::string clients_id;
	std::cout << "Enter clients id: ";
	std::getline(std::cin, clients_id);

	std::string telephone_number;
	std::cout << "Enter clients telephone number: ";
	std::getline(std::cin, telephone_number);

	pqxx::transaction t(c);

	t.exec_prepared("add_new_tel_number", 1, telephone_number, clients_id);

	t.commit();
}

// �����, ����������� �������� ������ �������

void change_clients_data(pqxx::connection& c)
{
	c.prepare("change_clients_data", "update clients set id = $1, first_name = $2, last_name = $3, e_mail = $4");
	
	std::string first_name;
	std::cout << "Enter clients first name: ";
	std::getline(std::cin, first_name);

	std::string last_name;
	std::cout << "Enter clients last name: ";
	std::getline(std::cin, last_name);

	std::string e_mail;
	std::cout << "Enter clients e-mail: ";
	std::getline(std::cin, e_mail);

	pqxx::transaction t(c);

	t.exec_prepared("change_clients_data", 1, first_name, last_name, e_mail);

	t.commit();
}

// �����, ����������� ������� ������� � ������������� �������

void delete_telephone(pqxx::connection& c)
{
	c.prepare("delete_telephone", "delete from telephones where id = $1");
	
	std::string clients_id;
	std::cout << "Enter clients id of client, telephone number of whom you want delete: ";
	std::getline(std::cin, clients_id);

	pqxx::transaction t(c);

	t.exec_prepared("delete_telephone", 1);

	t.commit();
}

// �����, ����������� ������� ������������� �������

void delete_client(pqxx::connection& c)
{
	c.prepare("delete_tel", "delete from telephones where id = $1");
	c.prepare("delete_clients", "delete from clients where id = $1");

	std::string clients_id;
	std::cout << "Enter clients id of client, whom you want delete: ";
	std::getline(std::cin, clients_id);

	pqxx::transaction t(c);

	t.exec_prepared("delete_tel", clients_id);
	t.exec_prepared("delete_clients", clients_id);

	t.commit();
}

int main()
{
	//setlocale(LC_ALL, "Russian");
	SetConsoleCP(CP_UTF8);
	SetConsoleOutputCP(CP_UTF8);
	setvbuf(stdout, nullptr, _IOFBF, 1000);
	try {
		pqxx::connection c(
			"host=127.0.0.1 "
			"port=5432 "
			"dbname=dbPqxxProject002 "
			"user=postgres "
			"password=111111");


	// �������� �����, ������� ������ ��� ������� � ����������� � �������.
		create_tables_if_not_exists(c);

		// ����� ���� ����� ������ ��� ������� ������� ������ �������, ���� �� ��������.
		std::cout << "If you want add new client, print 1, if you want add telephone to client, print 2," 
			"if you want change client's data, print 3, if you want delete tel number of exist client, print 4"
			"if you want delete exist client, print 5, if you want find client with his data print 6" 
			" if you want finished work, print 0"<< std::endl;

		
		
		int a;
		std::cout << "You decision: ";
		std::cin >> a;

		if (a == 1)
		{
		   // �������� �����, ������� ��������� ������ �������.
			add_new_client(c);
		}
		else if (a == 2)
		{
			// �������� �����, ������� ��������� �������� ������� �������
			add_new_telephone_number(c);
		}
		else if (a == 3)
		{
			// �������� �����, ������� ��������� �������� ������ � �������
			change_clients_data(c);
		}
		else if (a == 4)
		{
			// �������� �����, ������� ��������� ������� ������� � ������������� �������
			delete_telephone(c);
		}
		else if (a == 5)
		{
			// �������� �����, ����������� ������� ������������� �������
			delete_client(c);
		}
		else if (a == 6)
		{
			std::cout << "Sorry, we find right decision of this problem" << std::endl;
		}
		else
		{
			std::cout << "Finished work, good buy" << std::endl;
		}
		
		// �����, ����������� ����� ������� �� ��� ������ - �����, �������, ����������� ����� ��� ��������.


		/*
		std::string first_name;
		std::cout << "Enter clients first name: ";
		std::getline(std::cin, first_name);

		std::string last_name;
		std::cout << "Enter clients last name: ";
		std::getline(std::cin, last_name);

		std::string e_mail;
		std::cout << "Enter clients e-mail: ";
		std::getline(std::cin, e_mail);

		std::string telephone_number;
		std::cout << "Enter clients telephone number: ";
		std::getline(std::cin, telephone_number);
		*/
		/*
		pqxx::transaction t(c);

		t.exec("select first_name from clients where first_name = 'ser'; ");
		// or last_name in '" + last_name + "' or e_mail in '" + e_mail + "'" + first_name + "
		t.commit();
		*/

		// ������ �� ������ 197 �������� �� ���������. ��� ���������� � ���, ��� ��� ������� ������� �� ������,
		// �� �������, �������� � DBreaver �� �������� ����� ����������.
		// ���� �� ���� �� ������ ����������� � ��������� ������ � DBreaver, ������ ��������, 
		// ����� ���������� � ������� clients �� ������ ����� ������ ���� ������� � ������ ���� ����� - ser

		// �� �������, ��� ������?
		std::cout << "Good bye" << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}

	return 0;
}
