TEMPLATE = subdirs
CONFIG += ordered
SUBDIRS = app libsimpleT9
app.depends = libsimpleT9
