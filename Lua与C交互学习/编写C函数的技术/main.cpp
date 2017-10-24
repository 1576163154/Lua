#include<iostream>
#include"..\lua53\lua.hpp"

using namespace std;

int l_map(lua_State* l) {
	int i;
	
	luaL_checktype(l, 1, LUA_TTABLE);//��һ������������һ��table
	luaL_checktype(l, 2, LUA_TFUNCTION);// ��           ����

	int n = lua_rawlen(l, 1);

	for (i = 1; i <= n; i++) {
		lua_pushvalue(l, 2);
		lua_rawgeti(l, 1, i);
		lua_call(l, 1, 1);
		lua_rawseti(l, 1, i);
	}
}

void main() {
	lua_State* l =  luaL_newstate();
	luaL_openlibs(l);

	lua_newtable(l);





	system("pause");
}