<p><a href="https://www.asu.edu.eg/"><img align="right" src="https://ums.asu.edu.eg/images/logo.png" width="100" /></a></p>
<div align=left>
<h1>
  HPC 'Labs & practical Exams' Solutions
</h1>
</div>
<br>
<br>

### How to run the MPI project
- In the folder of the project go to `Debug` folder you can see now this file `theNameOfTheProject.exe`. Run the cmd there and write the following code :
```bash
mpiexec "nameOfTheProject.exe"
```
### How to run on a specefic number of processors
```bash
mpiexec -n 3 "nameOfTheProject.exe"
```
- The "3" is the number of the processrs you can write yours
