import os


def filter_str(text, in_filter, out_filter):
    '''
    text在out_filter,返回False
    in_filter不等于None,text在里边返回True,不在里边返回False
    in_filter等于None,返回True
    '''
    if in_filter is not None:
        assert (isinstance(in_filter, list) or isinstance(in_filter, tuple))

    if out_filter is not None:
        assert (isinstance(out_filter, list) or isinstance(out_filter, tuple))

    if out_filter is not None and text in out_filter:
        return False
    if in_filter is not None:
        if text in in_filter:
            return True
        else:
            return False
    else:
        return True


def list_all_files(rootdir, ext=None, non_ext=None):
    '''
    功能：获取目录下的所有文件
    输入：
        rootdir 目录，
        not_ext 排除指定后缀[.json,.txt],优先级高于ext,必须是列表或元祖
        ext     过滤指定后缀，为空不过滤比如[.png,.jpg],只返回.png和.jpg后缀(前提是not_ext里不包含此后缀),必须是列表或元祖
    输出：
        文件绝对路径列表
    '''
    _files = []
    list = os.listdir(rootdir)
    for i in range(0, len(list)):
        path = os.path.join(rootdir, list[i])
        if os.path.isdir(path):
            _files.extend(list_all_files(path, ext, non_ext))
        if os.path.isfile(path):
            if filter_str(os.path.splitext(path)[-1], ext, non_ext):
                _files.append(path)
    return _files


if __name__ == "__main__":
    dir = '../chapter'
    files = list_all_files(dir, ('.cpp', ))
    cmakeFIle = dir + "/CMakeLists.txt"
    print('文件总数：{},file: {}'.format(len(files), cmakeFIle))

    with open(cmakeFIle, 'w') as f:
        for name in files:
            # os.rename(f, f.replace("main-", "chapter_"))
            target = os.path.splitext(os.path.basename(name))[0]
            print(target)

            f.write('add_executable({} {}.cpp)\n'.format(target, target))
            f.write('target_include_directories({} PRIVATE {})\n'.format(
                target, '${CV_INCLUDE_DIRS}'))
            f.write('target_link_directories({} PRIVATE {})\n'.format(
                target, '${CV_LIBRARY_DIRS}'))
            f.write('target_link_libraries({} PRIVATE {})\n\n'.format(
                target, '${CV_LIBRARIES}'))
