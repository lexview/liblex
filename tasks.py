
from invoke import task

@task
def clean(c):
    c.run('rm -rf builddir')

@task(default=True, pre=[ clean ])
def build(c):
    c.run('meson builddir', pty=True)
    c.run('ninja -C builddir', pty=True)

@task
def check(c):
    c.run('ninja -C builddir test', pty=True)

