# options: -translation lf -encoding utf-8

proc ::InstallJammer::InitFiles {} {
    File ::3105EA2C-61FA-65BA-95C0-6677C4A931B6 -name Debug -parent 0CC21C96-ECDD-FF5D-C09C-52ABCC22D1EA -directory <%InstallDir%> -type dir -permissions 040755 -filemethod 0
    File ::A5CB07D7-DA6B-941E-3D60-04136AB524B2 -name serverNix -parent 0CC21C96-ECDD-FF5D-C09C-52ABCC22D1EA -directory <%InstallDir%> -size 25350 -mtime 1507141247 -permissions 00775 -filemethod 0

}
