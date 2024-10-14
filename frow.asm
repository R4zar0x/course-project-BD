.model flat, C
.data

.code

_tax proc bid:dword, percent:qword
	finit

	fld percent
	fild bid
	fmul
	fst percent
	fwait

	lea eax, percent
	ret
_tax endp

_pensionFund proc bid:dword, percent:qword
	finit

	fld percent
	fild bid
	fmul
	fst percent
	fwait

	lea eax, percent
	ret
_pensionFund endp

_employmentFund proc bid:dword, percent:qword
	finit

	fld percent
	fild bid
	fmul
	fst percent
	fwait

	lea eax, percent
	ret
_employmentFund endp

_spent proc tax:qword, pensionFund:qword, employmentFund:qword
	finit

    fld tax
    fadd pensionFund
    fadd employmentFund
    fst tax
    fwait

	lea eax, tax
	ret
_spent endp

_issuance proc bid:dword, spent:qword
	finit

    fild bid
    fsub spent
    fstp spent
    fwait

	lea eax, spent
	ret
_issuance endp

end