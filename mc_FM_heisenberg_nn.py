#!/usr/bin/env python
# coding: utf-8

# In[13]:


# Importing libraries
import numpy as np
import scipy as sp
import matplotlib.pyplot as plt
from random import random
import os

# To delete existing data (.txt) files
os.system ('rm *.txt')

# Define lattice dimensions
nx = 20 ; ny = 20 ; area= nx*ny
# Define various trigonometric functions
Pi = np.pi ; Cos = np.cos ; Sin = np.sin ; Acos = np.arccos
# Heisenberg coupling parameters and magnetic field strength
JH = -0.7 ; B = 0.0
# Spin magnitudes
spin = 1.0
# Define temperature range
min_Temp = 0.001 ; max_Temp = 1.0
# Define number of monte-carlo equilibration and avearging
Neq = 10000 ; Nav = 10000

# Initializing spin arrays on square lattice
sx = np.zeros((area,), dtype=float)
sy = np.zeros((area,), dtype=float)
sz = np.zeros((area,), dtype=float)
theta = np.zeros((area,), dtype=float)
phi = np.zeros((area,), dtype=float)

# Initial random configuration
for iy in range (ny):
    for ix in range (nx):
        i = (iy)*nx+ix
        r1 = random()
        phi[i] = ((60.0*r1))*2.0*Pi/60.0
        r2 = random()
        theta[i] = Acos((30.0*r2)/(30.0))
        r3 = random()
        if r3 > 0.5:
            theta[i] = Pi -theta[i]
        sx[i] = spin*Sin(theta[i])*Cos(phi[i])
        sy[i] = spin*Sin(theta[i])*Sin(phi[i])
        sz[i] = spin*Cos(theta[i])
        
# Defining temperature grid
temperature = np.linspace (0.001, 1.0, 90)

f1 = open('energy_vs_Temperature.txt', 'a+')
f2 = open('magnetization_vs_Temperature.txt', 'a+')

for i_temp in range (temperature.shape[0]):
    temp = temperature [temperature.shape[0]-(i_temp+1)]
    print('%6i %10.3f \n' %(i_temp, temp))
    
    avE = 0.0
    avmx = 0.0 ; avmy = 0.0 ; avmz = 0.0 ; avmag = 0.0
    
    for iter in range (Neq + Nav):
        for iy in range (ny):
            for ix in range (nx):
                i = iy*nx + ix
                
                jx = ix + 1 ; jy = iy
                if (jx > nx-1):
                    jx = 0
                j1 = jy*nx + jx
                jx = ix ; jy = iy + 1
                if (jy > ny-1):
                    jy = 0
                j2 = jy*nx + jx
                jx = ix - 1 ; jy = iy
                if (jx < 0):
                    jx = nx-1
                j3 = jy*nx + jx
                jx = ix ; jy = iy - 1
                if (jy < 0):
                    jy = ny-1
                j4 = jy*nx + jx
                
#                 print(ix, iy, i, j1, j2, j3, j4)
                
                Eng_JH = JH * ( sx[i]*(sx[j1] + sx[j2] + sx[j3] + sx[j4])
                            +   sy[i]*(sy[j1] + sy[j2] + sy[j3] + sy[j4])
                            +   sz[i]*(sz[j1] + sz[j2] + sz[j3] + sz[j4]) )
                Eng_B = -B * sz[i]
                E_old = Eng_JH + Eng_B
                
                phi_temp = phi[i] ; theta_temp = theta[i]
                r1 = random()
                phi[i] = ((60.0*r1))*2.0*Pi/60.0
                r2 = random()
                theta[i] = Acos((30.0*r2)/(30.0))
                r3 = random()
                if r3 > 0.5:
                    theta[i] = Pi -theta[i]
                sx[i] = spin*Sin(theta[i])*Cos(phi[i])
                sy[i] = spin*Sin(theta[i])*Sin(phi[i])
                sz[i] = spin*Cos(theta[i])
                
                Eng_JH = JH * ( sx[i]*(sx[j1] + sx[j2] + sx[j3] + sx[j4])
                            +   sy[i]*(sy[j1] + sy[j2] + sy[j3] + sy[j4])
                            +   sz[i]*(sz[j1] + sz[j2] + sz[j3] + sz[j4]) )
                Eng_B = -B * sz[i]
                E_new = Eng_JH + Eng_B
                
                diffE = E_new - E_old
                
                seed = random()
                if np.abs(diffE/temp) < 8.0:
                    prob = np.exp(-diffE/temp)
                else:
                    prob = 0.0

                if diffE <= 0.0:
                    conf = 'newconf'
                else:
                    if prob > seed:
                        conf = 'newconf'
                    else:
                        conf =  'oldconf'

                if conf == 'oldconf':
                    theta[i] = theta_temp
                    phi[i] = phi_temp

                sx[i] = spin*Sin(theta[i])*Cos(phi[i])
                sy[i] = spin*Sin(theta[i])*Sin(phi[i])
                sz[i] = spin*Cos(theta[i])
        
        if iter > Neq:
            
            mx = 0.0
            my = 0.0
            mz = 0.0
            for iy in range(ny):
                for ix in range (nx):
                    i=(iy-1)*nx+ix
                    mx = mx + sx[i] ; my = my + sy[i] ; mz = mz + sz[i]
       
            mx = mx/(area) ; my = my/(area) ; mz = mz/(area)
            avmx = avmx + mx ; avmy = avmy + my ; avmz = avmz + mz
            avmag = avmag + np.sqrt(mx**2+my**2+mz**2)
            
            Eng = 0.0
            for iy in range (ny):
                for ix in range (nx):
                    i = iy*nx + ix
                    jx = ix + 1 ; jy = iy
                    if (jx > nx-1):
                        jx = 0
                    j1 = jy*nx + jx
                    jx = ix ; jy = iy - 1
                    if (jy > ny-1):
                        jy = 0
                    j2 = jy*nx + jx
                    Eng_JH = JH * ( sx[i]*(sx[j1] + sx[j2]) + sy[i]*(sy[j1] + sy[j2]) + sz[i]*(sz[j1] + sz[j2]) )
                    Eng_B = - B * sz[i]
                    Eng = Eng_JH + Eng_B
            avE = avE + Eng/(area)
    
    avmx = avmx/(Nav); avmy = avmy/(Nav) ; avmz = avmz/(Nav) ; avmag = avmag/(Nav) ; avE = avE/Nav
    f1.write ('%12.4f %12.4f \n' %(temp, avE))
    f2.write ('%12.4f %12.4f %12.4f %12.4f %12.4f \n' %(temp, avmag,avmx,avmy,avmz))
    
    for iy in range(ny):
        for ix in range (nx):
            i=(iy-1)*nx+ix
            str_temp = "temp_%.2f" % temp
            f3 = open (str_temp+'_spin_config.txt', 'a+')
            f3.write ('%6i %6i %6i %12.4f %12.4f %12.4f %12.4f %12.4f \n'
                       %(ix, iy, i, sx[i], sy[i], sz[i], theta[i], phi[i]))
    f3.close()
f1.close()
f2.close()

mag = np.genfromtxt ('magnetization_vs_Temperature.txt')

plt.plot (mag[:,0], mag[:,1], color='b')


# In[ ]:




