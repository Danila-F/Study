import math


def num_arr_to_str_arr(num_arr):
    str_arr = []
    for i in range(len(num_arr)):
        str_arr.append(str(num_arr[i]))
    return str_arr


def strs_arr_length(strs):
    len_arr = []
    for i in range(len(strs)):
        len_arr.append(len(strs[i]))
    return len_arr


def str_to_right_corn(string_, length):
    return ' ' * (length - len(string_)) + string_


def str_to_left_corn(string_, length):
    return string_ + ' ' * (length - len(string_))


def str_to_center(string_, length):
    return ' ' * math.ceil((length - len(string_)) / 2) + string_ + ' ' * math.floor((length - len(string_)) / 2)


def strs_alignment(align_func, index, strs):
    return align_func(strs[index], max(strs_arr_length(strs)))


def column_with_alignment(strs, align_type='left'):
    column = ''
    if align_type == 'right':
        align_func = str_to_right_corn
    elif align_type == 'center':
        align_func = str_to_center
    else:
        align_func = str_to_left_corn
    for i in range(len(strs)):
        column = column + strs_alignment(align_func, i, strs) + '\n'
    return column[:-1]


class Table:
    def __init__(self,
                 rows=0,
                 columns=0,
                 def_cell_size=1,
                 def_cell_type="string",
                 def_cell_align="left",
                 def_cell_format='',
                 def_col_sep="|",
                 def_row_sep="-"):
        self.rows = rows
        self.columns = columns
        self.def_cell_size = def_cell_size
        self.def_cell_type = def_cell_type
        self.def_cell_align = def_cell_align
        self.def_cell_format = def_cell_format
        self.def_col_sep = def_col_sep
        self.def_row_sep = def_row_sep
        self.arr = self.create_arr()

    def create_arr(self):
        return [[self.new_cell()] * self.columns] * self.rows

    def new_cell(self,
                 content="",
                 size=None,
                 align=None,
                 cell_type=None,
                 cell_format=None,
                 row_sep=None,
                 col_sep=None):
        return {"content": content,
                "size": size if size is not None else self.def_cell_size,
                "align": align if align is not None else self.def_cell_align,
                "type": cell_type if cell_type is not None else self.def_cell_type,
                "format": cell_format if cell_format is not None else self.def_cell_format,
                "top_sep": row_sep if row_sep is not None else self.def_row_sep,
                "bottom_sep": row_sep if row_sep is not None else self.def_row_sep,
                "left_sep": col_sep if col_sep is not None else self.def_col_sep,
                "right_sep": col_sep if col_sep is not None else self.def_col_sep}

    def new_row(self):
        pass

    def size(self):
        return [self.columns, self.rows]


table1 = Table(rows=2, columns=2)
print("size is", table1.size())
