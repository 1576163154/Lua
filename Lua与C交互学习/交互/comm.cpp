#include "..\lua53\lua.hpp"
#include<stdio.h>
#include<iostream>

using namespace std;

struct ColorTable
{
	char* name;
	unsigned char red;
	unsigned char green;
	unsigned char blue;
} ct[] = {
	{"WHITE",1,1,1},
	{"RED",1,0,0},
	{"NULL",0,0,0},
	
};

//����һ��table ѹ�� lua������ȥ
void setColor(lua_State* l, ColorTable* ct) {
	lua_newtable(l);
	lua_pushnumber(l, ct->red);
	lua_setfield(l, -2, "r");

	lua_pushnumber(l, ct->green);
	lua_setfield(l, -2, "g");

	lua_pushnumber(l, ct->blue);
	lua_setfield(l, -2, "b");

	lua_setglobal(l, ct->name);//����talbe�����޸ı������
}



//����lua�ļ�
void load(lua_State* l, const char* name, int* w, int* h) {
	if (luaL_loadfile(l, name) || lua_pcall(l, 0, 0, 0)) {
		printf("cannot run lua file : %s\n", lua_tostring(l, -1));
	}
	lua_getglobal(l, "width");
	if (!lua_isnumber(l, -1)) {
		//���������Ϣ
	}

	lua_getglobal(l, "height");
	if (!lua_isnumber(l, -1)) {
		//ͬ��
	}

	*w = lua_tonumber(l, -2);
	*h = lua_tonumber(l, -1);

	lua_settop(l, 0);//���ջ
}



void main() {
	lua_State* l = luaL_newstate();
	luaL_openlibs(l);
	int w = 0;
	int h = 0;
	load(l, "test.lua", &w, &h);

	////////////////////////////��Lua�ļ��л�ȡ

	lua_getglobal(l, "bg");//��ȡ bg {},
	lua_pushstring(l, "r");//ѹ�� key ��r��
	lua_gettable(l, -2);//��ȡ bg[r]
	cout << lua_gettop(l) << endl;
	double red = lua_tonumber(l, -1);
	
	cout << lua_gettop(l) << endl;
	lua_settop(l, 1);
	

	//��ȡ bg[g]
	lua_pushstring(l, "g");
	lua_gettable(l, -2);
	double green = lua_tonumber(l, -1);


	////��ȡ bg[b]
	lua_settop(l, 1);
	/*lua_pushstring(l, "b");
	lua_gettable(l, -2);*/

	//�ɻ�Ϊ
	lua_getfield(l, -1, "b");//����û����ջ�� ѹ�� key����table λ��-1
	double blue = lua_tonumber(l, -1);

	////////////////////////////��Lua�ļ������table

	int count = 0;
	while (ct[count].name != NULL) {
		setColor(l, &ct[count++]);
	}

	//��ʱ�ٴ�Lua������ȡ�ո���ӵ� Color
	lua_getglobal(l, "WHITE");
	lua_pushstring(l, "r");//ѹ�� key ��r��
	lua_gettable(l, -2);//��ȡ bg[r]
	cout << lua_tonumber(l, -1) << endl;
	system("pause");
}