[Soal 1](#soal-1)  
[Soal 2](#soal-2)  
[Soal 3](#soal-3)  
[Soal 4](#soal-4)  
[Soal 5](#soal-5)  

## Soal 1
Elen mempunyai pekerjaan pada studio sebagai fotografer. Suatu hari ada seorang klien yang bernama Kusuma yang meminta untuk mengubah nama file yang memiliki ekstensi .png menjadi “[namafile]_grey.png”. Karena jumlah file yang diberikan Kusuma tidak manusiawi, maka Elen meminta bantuan kalian untuk membuat suatu program C yang dapat mengubah nama secara otomatis dan diletakkan pada direktori /home/[user]/modul2/gambar.

Catatan : Tidak boleh menggunakan crontab.

#### Penyelesaian
```
static void StripFileName(char *FileName, char *NewFileName)
{
    int PLocation;
    int i;
    int x;

    i = strlen(FileName) - 1;
    
    while (i && FileName[i] != '.')
    {
        i--;
    }

    if (i)
    {
        PLocation = i;
    }
    else
    {
        PLocation = strlen(FileName);
        i = strlen(FileName) - 1;
    }

    while (i && FileName[i] != '\\')
    {
        if (FileName[i] != '\\')
        i--;
    }

    if (FileName[i] == '\\')
        i++;
        x = 0;

    while (i < PLocation)
    {
        NewFileName[x] = FileName[i];
        x++;
        i++;
    }
    NewFileName[x] = '\0';
}
```
Fungsi ``` static void StripFileName(char *FileName, char *NewFileName) ``` digunakan untuk mengambil namafile tanpa ekstensi. 
```
DIR *d;
struct dirent *dir;
char folder[100] = "/home/ismail/modul2/gambar/";
char folderl[100] = "/home/ismail/Pictures/";
d = opendir("/home/ismail/Pictures/");
```
inisialisasi variabel yang dibutuhkan.  
 ```while ((dir =  readdir(d)) !=  NULL)```  
mengecek setiap file yang ada dalam folder ("/home/ismail/Pictures")  
```ext =  strchr(fullname,'.');```  
mendapatkan ekstensi dari nama file. string setelah titik akan diambil  
``` if(strcmp(ekstensi, ".png") ==  0)```  
mengecek apakah ekstensi dari file tersebut adalah ".png"  
```
strcat(newname, grey);
strcat(newname, ekstensi);
```
menambahkan isi dari string grey ke nama file tanpa ekstensi kemudian ditambahkan ekstensi file.
```
strcat(foldertemp, newname);
strcpy(newname, foldertemp);
```
menambahkan lokasi tujuan file pada nama file yang baru.
```
strcat(foldertemp, fullname);
strcpy(fullname, foldertemp);
```
menambahkan lokasi asal file pada nama file yang akan di rename  
``` rename(fullname, newname); ```  
mengubah nama file menjadi nama file yang baru  
``` sleep(5); ```  
menjalankan setiap 5 detik
## Soal 2
Pada suatu hari Kusuma dicampakkan oleh Elen karena Elen dimenangkan oleh orang lain. Semua kenangan tentang Elen berada pada file bernama “elen.ku” pada direktori “hatiku”. Karena sedih berkepanjangan, tugas kalian sebagai teman Kusuma adalah membantunya untuk menghapus semua kenangan tentang Elen dengan membuat program C yang bisa mendeteksi owner dan group dan menghapus file “elen.ku” setiap 3 detik dengan syarat ketika owner dan grupnya menjadi “www-data”. Ternyata kamu memiliki kendala karena permission pada file “elen.ku”. Jadi, ubahlah permissionnya menjadi 777. Setelah kenangan tentang Elen terhapus, maka Kusuma bisa move on.

Catatan: Tidak boleh menggunakan crontab

#### Penyelesaian
```
int i;
struct stat sb;
char dir[100] = "/home/ismail/sisop/SoalShift_modul2_B13/Soal2/hatiku/elen.ku";
```
inisialiasi variabel yang akan digunakan
```
stat(dir, &sb);
struct passwd *pw = getpwuid(sb.st_uid);
struct group  *gr = getgrgid(sb.st_gid);
```
inisialisasi pointer pw dengan struct passwd dan pointer gr dengan struct group
```chmod (dir, 0777)```
mengubah file permission dari file elen.ku
```
if((strcmp(pw->pw_name, "www-data") ==  0) && (strcmp(gr->gr_name, "www-data") ==  0))
``` 
mengecek apakah owner dan group adalah "www-data"  
```remove(dir)```  
menghapus file jika memenuhi syarat sebelumnya  
``` sleep(3); ```  
menjalankan setiap 3 detik  

## Soal 3
Diberikan file campur2.zip. Di dalam file tersebut terdapat folder “campur2”.  
Buatlah program C yang dapat :  
i) mengekstrak file zip tersebut.  
ii) menyimpan daftar file dari folder “campur2” yang memiliki ekstensi .txt ke dalam file daftar.txt.  

Catatan:
-   Gunakan fork dan exec.
-   Gunakan minimal 3 proses yang diakhiri dengan exec.
-   Gunakan pipe
-   Pastikan file daftar.txt dapat diakses dari text editor

#### Penyelesaian
```
int status;
int p1[4];
pipe(p1);
pipe(p1+2);
pid_t pID;
```
inisialisasi variabel yang dibutuhkan dan membuat pipe
```
char  *argv[3] ={"unzip","/home/ismail/sisop/SoalShift_modul2_B13/Soal3/campur2.zip", NULL};
execv("/usr/bin/unzip", argv);
```
unzip file campur2.zip
```
while ((wait(&status)) >  0);
```
menunggu proses sebelumnya selesai
```
close(p1[0]);
close(p1[2]);
close(p1[3]);
dup2(p1[1],1);
char  *argv[3] = {"ls","/home/ismail/sisop/SoalShift_modul2_B13/Soal3/campur2", NULL};
execv("/bin/ls", argv);
```
list file yang ada pada folder campur2 dan mengirim output lewat pipe
```
close(p1[1]);
close(p1[2]);
dup2(p1[0],0);
dup2(p1[3],1);
char  *argv[3] = {"grep", ".txt$", NULL};
execv("/bin/grep", argv);
```
grep file hasil output perintah sebelumnya yang didapatkan lewat pipe yang memiliki ekstensi ".txt"
```
close(p1[0]);
close(p1[1]);
close(p1[3]);
FILE *mfile;
char data[1000];
mfile = fopen ("/home/ismail/sisop/SoalShift_modul2_B13/Soal3/daftar.txt", "w");
read(p1[2], data, 1000);
fputs(data, mfile);
fclose(mfile);
```
mendapatkan hasil output sebelumnya lewat pipe dan membuat file serta menulis isi file dari output tersebut ke dalam file

## Soal 4

Dalam direktori /home/[user]/Documents/makanan terdapat file makan_enak.txt yang berisikan daftar makanan terkenal di Surabaya. Elen sedang melakukan diet dan seringkali tergiur untuk membaca isi makan_enak.txt karena ngidam makanan enak. Sebagai teman yang baik, Anda membantu Elen dengan membuat program C yang berjalan setiap 5 detik untuk memeriksa apakah file makan_enak.txt pernah dibuka setidaknya 30 detik yang lalu (rentang 0 - 30 detik).  
Jika file itu pernah dibuka, program Anda akan membuat 1 file makan_sehat#.txt di direktori /home/[user]/Documents/makanan dengan '#' berisi bilangan bulat dari 1 sampai tak hingga untuk mengingatkan Elen agar berdiet.
 
Contoh:
File makan_enak.txt terakhir dibuka pada detik ke-1
Pada detik ke-10 terdapat file makan_sehat1.txt dan makan_sehat2.txt

Catatan:
 -   dilarang menggunakan crontab
 -   Contoh nama file : makan_sehat1.txt, makan_sehat2.txt, dst

#### Penyelesaian
```
char nama[15]="makan_enak";
char eks[5]=".txt";
char namafile[30];
char temp[30];
char angka[10];
struct stat filestat;
```
inisialisasi variabel yang akan digunakan
```
stat("makan_enak.txt",&filestat);
```
mendapatkan status file "makan_enak.txt"
```
time_t timenow;
time(&timenow);
```
mendapatkan waktu saat ini
```
int waktu =  difftime(timenow, filestat.st_atime);
```
mendapatkan waktu(detik) file terakhir di akses
```if(waktu <=  30)```
mengecek apakah waktu terakhir diakses kurang dari 30 detik yang lalu
``` sprintf(angka, "%d", i); ```
mengubah tipe data integer menjadi string
```
strcpy(namafile, nama);
strcat(namafile, angka);
strcat(namafile, eks); 
```
menambahkan nama file dengan angka(sesuai dengan nomor file yang akan dibuat) dan menambahkan ekstensi
```
FILE* fo;

fo = fopen (namafile, "w+");
fclose(fo);
```
inisialiasi dan membuat file sesuai dengan namafile yang telah di dapatkan sebelumnya  
``` sleep(5); ```  
menjalankan setiap 5 detik  

## Soal 5
Kerjakan poin a dan b di bawah:
a.  Buatlah program c untuk mencatat log setiap menit dari file log pada  syslog ke /home/[user]/log/[dd:MM:yyyy-hh:mm]/log#.log
Ket:
-	Per 30 menit membuat folder /[dd:MM:yyyy-hh:mm]
-   Per menit memasukkan log#.log ke dalam folder tersebut ‘#’ : increment per menit. Mulai dari 1

b.  Buatlah program c untuk menghentikan program di atas.
    
NB: Dilarang menggunakan crontab dan tidak memakai argumen ketika menjalankan program.
