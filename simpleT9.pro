TEMPLATE = subdirs
CONFIG += ordered
SUBDIRS = libsimpleT9 app test

app.depends = libsimpleT9
test.depends = libsimpleT9
