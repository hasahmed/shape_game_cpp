# 2/16/19

MEMORY LEAK POTENTIAL RESOLUTION
Realized source of memory leak alhamdulilah.
The issue is that when removing a multishape only one renderpackage is removed with it despite the fact that
the multishape has many renderpackages associated with it. God willing fixing that will solve the issue


# 2/16/19
Realized that current 'simple' implementation of adding multishapes to the scene will not work.
It doesn't consider that a multishape might have a multishape as a child. Due to the recursive
nature of such nestings it is necessary to have the adding of multishapes (and accounting for their subsequent
removal) will take a bit more work
