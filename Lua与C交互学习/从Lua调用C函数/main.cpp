#include "..\lua53\lua.hpp" 
#include<iostream>


using namespace std;

//��һ������ƽ��
static int square(lua_State* l) {
	

	//double a = lua_tonumber(l, 1);//��ȡ����
	//Ҳ������
	double a = luaL_checknumber(l, 1);

	//���д����������ѹ��
	lua_pushnumber(l, a*a);
	return 1;//����ֵ��ʾ����������������ں�ջ��������ֵ���ֿ�

	//return ��ջ�к���������µ�Ԫ�ػᵯ��ջ������֤�������ý����1��ʼ
}


//�ֱ�����������ƽ��
static int twoSquare(lua_State* l) {
	double a = luaL_checknumber(l, 1);
	double b = luaL_checknumber(l, 2);
	lua_pushnumber(l, a*a);
	lua_pushnumber(l, b*b);
	return 2;
}

//C���� ����
static const  luaL_Reg CFuncs[] = {
	{"square",square},
	{"twoSquare",twoSquare},
	{0,0}, //������β
};


void main() {
	
	lua_State* l = luaL_newstate();
	luaL_openlibs(l);
	
	//load lua file
	luaL_loadfile(l, "D:\\IDE\\vsproject\\Lua\\Lua��C����ѧϰ\\��Lua����C����\\test.lua");

	//ע��C���������ݺ�����ַ��Lua����
	lua_pushcfunction(l, square);
	lua_setglobal(l, "square");//��������������Ϊ ��square����ȫ�֣�

	 //�����C��������һ��ģ�����ʽע�ᵽLua
	lua_pushcfunction(l, twoSquare);
	lua_setglobal(l, "twoSquare");

	luaL_dofile(l, "D:\\IDE\\vsproject\\Lua\\Lua��C����ѧϰ\\��Lua����C����\\test.lua");


	
	



	system("pause");
}