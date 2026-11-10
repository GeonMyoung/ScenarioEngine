"""Protect operational configuration snapshots; users enter credentials in the UI."""
import ctypes as C
import os

class Blob(C.Structure):
    _fields_=[('size',C.c_uint32),('data',C.c_void_p)]

def _crypt(data,decrypt=False):
    if os.name!='nt':raise ValueError('Windows 사용자 보호 저장소를 사용할 수 없습니다.')
    crypt=C.WinDLL('crypt32',use_last_error=True);kernel=C.WinDLL('kernel32',use_last_error=True)
    buf=C.create_string_buffer(data);source=Blob(len(data),C.cast(buf,C.c_void_p));target=Blob()
    f=crypt.CryptUnprotectData if decrypt else crypt.CryptProtectData
    f.restype=C.c_int
    f.argtypes=[C.POINTER(Blob),C.c_void_p,C.c_void_p,C.c_void_p,C.c_void_p,C.c_uint32,C.POINTER(Blob)]
    if not f(C.byref(source),None,None,None,None,1,C.byref(target)):
        raise ValueError('인증정보 보호 처리에 실패했습니다. 같은 Windows 사용자로 설정을 다시 입력하세요.')
    kernel.LocalFree.argtypes=[C.c_void_p];kernel.LocalFree.restype=C.c_void_p
    try:return C.string_at(target.data,target.size)
    finally:
        if target.data:C.memset(target.data,0,target.size);kernel.LocalFree(target.data)

def protect(config):
    value=dict(config)
    password=value.pop('password',None)
    if password:
        value['password_protected']='dpapi-v1:'+_crypt(password.encode('utf-8')).hex()
    elif password is not None:value['password']=''
    return value

def unprotect(config):
    value=dict(config)
    protected=value.pop('password_protected',None)
    if protected:
        if value.get('password'):raise ValueError('인증 입력 형식이 중복되었습니다.')
        try:
            if not protected.startswith('dpapi-v1:'):raise ValueError()
            value['password']=_crypt(bytes.fromhex(protected[9:]),True).decode('utf-8')
        except (TypeError,ValueError,UnicodeError):
            raise ValueError('보관된 인증정보를 읽지 못했습니다. Username·Password를 다시 입력하세요.') from None
    return value

def validate(config):
    for key in ('username','password'):
        value=config.setdefault(key,'')
        if not isinstance(value,str) or '\0' in value or len(value.encode('utf-8'))>65535:
            raise ValueError(key+': 문자열 형식과 길이를 확인하세요.')
    if config['password'] and not config['username']:raise ValueError('Password를 사용하려면 Username도 입력하세요.')

def connection(config):
    result={}
    if config.get('username'):result.update(username=config['username'],password=config.get('password',''))
    if config.get('ca_file'):result['ca_file']=config['ca_file']
    return result
