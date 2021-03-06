
#include "PluginYoutubeLuaHelper.h"
#include "PluginYoutube/PluginYoutube.h"
#include "CCLuaEngine.h"
#include "tolua_fix.h"
#include "SDKBoxLuaHelper.h"

class YoutubeListenerLua : public sdkbox::YoutubeListener {
public:
    YoutubeListenerLua(): mLuaHandler(0) {

    }
    ~YoutubeListenerLua() {
        resetHandler();
    }

    void setHandler(int luaHandler) {
        if (mLuaHandler == luaHandler) {
            return;
        }
        resetHandler();
        mLuaHandler = luaHandler;
    }

    void resetHandler() {
        if (0 == mLuaHandler) {
            return;
        }

        LUAENGINE->removeScriptHandler(mLuaHandler);
        mLuaHandler = 0;
    }

    void onPlayEnds(bool played_ok)
    {
        LuaStack* stack = LUAENGINE->getLuaStack();

        LuaValueDict dict;
        dict.insert(std::make_pair("name", LuaValue::stringValue("onPlayEnds")));
        dict.insert(std::make_pair("played_ok", LuaValue::booleanValue(played_ok)));
        stack->pushLuaValueDict(dict);
        stack->executeFunctionByHandler(mLuaHandler, 1);
    }

private:
    int mLuaHandler;
};

int lua_PluginYoutubeLua_PluginYoutube_setListener(lua_State* tolua_S) {
    int argc = 0;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"sdkbox.PluginYoutube",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
#if COCOS2D_DEBUG >= 1
        if (!toluafix_isfunction(tolua_S, 2 , "LUA_FUNCTION",0,&tolua_err))
        {
            goto tolua_lerror;
        }
#endif
        LUA_FUNCTION handler = (  toluafix_ref_function(tolua_S,2,0));
        YoutubeListenerLua* lis = static_cast<YoutubeListenerLua*> (sdkbox::PluginYoutube::getListener());
        if (nullptr == lis) {
            lis = new YoutubeListenerLua();
        }
        lis->setHandler(handler);
        sdkbox::PluginYoutube::setListener(lis);

        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "sdkbox.PluginYoutube::setListener",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_PluginYoutubeLua_PluginYoutube_setListener'.",&tolua_err);
#endif
    return 0;
}

int extern_PluginYoutube(lua_State* L) {
    if (nullptr == L) {
        return 0;
    }

    lua_pushstring(L, "sdkbox.PluginYoutube");
    lua_rawget(L, LUA_REGISTRYINDEX);
    if (lua_istable(L,-1))
    {
        tolua_function(L,"setListener", lua_PluginYoutubeLua_PluginYoutube_setListener);
    }
    lua_pop(L, 1);

    return 1;
}

TOLUA_API int register_all_PluginYoutubeLua_helper(lua_State* L) {
    tolua_module(L,"sdkbox",0);
    tolua_beginmodule(L,"sdkbox");

    extern_PluginYoutube(L);

    tolua_endmodule(L);
    return 1;
}


