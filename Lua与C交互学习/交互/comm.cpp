#include "..\lua53\lua.hpp"
#include<stdio.h>
#include<iostream>

using namespace std;






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
	system("pause");
}