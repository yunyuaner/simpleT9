TEMPLATE = subdirs
CONFIG += ordered
SUBDIRS = libsimpleT9 app
app.depends = libsimpleT9
