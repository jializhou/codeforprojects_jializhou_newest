#
# Hao, created: 01/20/2015, modified: 01/22/2015
#

import re
import sqlite3

#

def db_open(env, init):
    #
    conn = sqlite3.connect(env["db_file_path"])
    if init == True:
        cursor = conn.cursor()
        cursor.execute("drop table if exists Product")
        cursor.execute("""
            create table Product (
                `id` int, `name` text, `price` int)
            """)
        cursor.execute("""
            insert into Product values (
                %s, '%s', %s)
            """ % ('1', 'air cleaner', '80'))
        cursor.execute("""
            insert into Product values (
                %s, '%s', %s)
            """ % ('2', 'apple pie', '50'))
        cursor.execute("""
            insert into Product values (
                %s, '%s', %s)
            """ % ('3', 'banana pie', '60'))
        cursor.execute("""
            insert into Product values (
                %s, '%s', %s)
            """ % ('4', 'apple tree', '90'))
        cursor.execute("""
            insert into Product values (
                %s, '%s', %s)
            """ % ('5', '3D printer', '500'))
        cursor.execute("""
            insert into Product values (
                %s, '%s', %s)
            """ % ('6', 'pacific aquarium', '500'))
        conn.commit()
    return conn

#

def db_close(conn):
    #
    conn.close()

#

def db_dump(conn, env):
    #
    cursor = conn.cursor()
    cursor.execute("""
        select * from %s
        """ % (env["table_name"]))
    for row in cursor:
        print row

#

def db_build_index(conn, env):
    #
    # Build keyword table and keyword-kid map
    #
    cursor = conn.cursor()
    cursor.execute("""
        select `%s`, `%s` from %s
        """ % (env["column_name_id"],
               env["column_name_index"],
               env["table_name"]))
    s_keyword = set()
    for row in cursor:
        v_word = split(row[1])
        for word in v_word:
            if word != "" and word not in s_keyword:
                s_keyword.add(word)
    v_keyword = sorted(s_keyword)
    m_keyword_kid = dict()
    cursor.execute("drop table if exists Keyword")
    cursor.execute("create table Keyword (`kid` int, `str` text)")
    for kid in range(0, len(v_keyword)):
        m_keyword_kid[v_keyword[kid]] = kid
        cursor.execute("""
            insert into Keyword values (%s, '%s')
            """ % (str(kid), v_keyword[kid]))
    conn.commit()
    #
    cursor.execute("select * from Keyword")
    for row in cursor:
        print row
    #
    # Build prefix table and prefix-lkid-rkid map
    #
    m_prefix_lkid_ukid = dict()
    for kid in range(0, len(v_keyword)):
        keyword = v_keyword[kid]
        for j in range(0, len(keyword)):
            prefix = keyword[0:(j + 1)]
            if prefix in m_prefix_lkid_ukid:
                m_prefix_lkid_ukid[prefix][1] = kid
            else:
                m_prefix_lkid_ukid[prefix] = [kid, kid]
    cursor.execute("drop table if exists Prefix")
    cursor.execute("create table Prefix (`str` text, `lkid` int, `ukid` int)")
    for prefix in sorted(m_prefix_lkid_ukid):
        [lkid, ukid] = m_prefix_lkid_ukid[prefix]
        cursor.execute("""
            insert into Prefix values ('%s', %s, %s)
            """ % (prefix, str(lkid), str(ukid)))
    conn.commit()
    #
    cursor.execute("select * from Prefix")
    for row in cursor:
        print row
    #
    # Build inverted index table
    #
    cursor2 = conn.cursor()
    cursor2.execute("drop table if exists InvIdx")
    cursor2.execute("create table InvIdx (`kid` int, `rid` int)")
    cursor.execute("""
        select `%s`, `%s` from %s
        """ % (env["column_name_id"],
               env["column_name_index"],
               env["table_name"]))
    for row in cursor:
        rid = int(row[0])
        v_word = split(row[1])
        for word in v_word:
            kid = m_keyword_kid[word]
            cursor2.execute("""
                insert into InvIdx values (%s, %s)
                """ % (str(kid), str(rid)))
    conn.commit()
    #
    cursor.execute("select * from InvIdx")
    for row in cursor:
        print row
    #
    # Create indexes
    #
    cursor.execute("create index idx_1 on %s (`id`)" % env["table_name"])
    cursor.execute("create index idx_2 on Prefix (`str`)")
    cursor.execute("create index idx_3 on InvIdx (`kid`)")
    cursor.execute("create index idx_4 on InvIdx (`rid`)")
    conn.commit()

#

def db_search(conn, env, query):
    #
    sql = ""
    v_prefix = split(query)
    for prefix in v_prefix:
        if prefix == "":
            continue
        if sql != "":
            sql += "intersect"
        sql += """
            select %s.* from Prefix, InvIdx, %s
            where Prefix.`str` = '%s' and
                Prefix.lkid <= InvIdx.kid  and
                InvIdx.kid  <= Prefix.ukid and
                InvIdx.rid = %s.id
            """ % (env["table_name"],
                   env["table_name"],
                   prefix,
                   env["table_name"])
    if sql != "":
        cursor = conn.cursor()
        cursor.execute(sql)
        for row in cursor:
            print row

#

def split(s):
    #
    return re.split(r"[^\w]+", s)

#

if __name__ == "__main__":
    #
    env = {
        "db_file_path":      "./test.db",
        "table_name":        "Product",
        "column_name_id":    "id",
        "column_name_index": "name"}
    #conn = db_open(env, True)
    #db_dump(conn, env)
    #db_build_index(conn, env)
    conn = db_open(env, False)
    print ">>>> 'a'"
    db_search(conn, env, "a")
    print ">>>> 'a p'"
    db_search(conn, env, "a p")
    print ">>>> 'a pa'"
    db_search(conn, env, "a  pa ")
    #v_word = re.split(r"[^\w]+", "abc66 def.9! 203")
    #print v_word
    db_close(conn)

#
##
###
##
#
#
##
###
##
#
#
##
###
##
#
#
##
###
##
#
#
##
###
##
#

