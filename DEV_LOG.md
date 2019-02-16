# 2/16/19

MEMORY LEAK POTENTIAL RESOLUTION
Realized source of memory leak alhamdulilah.
The issue is that when removing a multishape only one renderpackage is removed with it despite the fact that
the multishape has many renderpackages associated with it. God willing fixing that will solve the issue