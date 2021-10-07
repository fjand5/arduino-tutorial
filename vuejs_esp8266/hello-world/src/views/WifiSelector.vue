<template>
  <el-drawer
  :append-to-body="true"
  title="I am the title"
  :visible.sync="drawer"
  direction="rtl">
    <el-table
      :data="getNearWifi"
      style="width: 100%">
      <el-table-column
        prop="ssid"
        label="Wifi"
        width="140">
      </el-table-column>
      <el-table-column
        prop="rssi"
        label="Sóng"
        width="60">
      </el-table-column>
      <el-table-column
        width="100">
      <template slot-scope="scope">
         <el-button 
         type="primary" 
         plain
         @click="selectWifi(scope.row)"
         >Chọn</el-button>
      </template>
      </el-table-column>
    </el-table>

    <el-dialog 
    title="Nhập mật khẩu" 
    :visible.sync="showPasswordConfirm"
    :append-to-body="true"
    >
      <el-input 
      v-model="password"
      type="password"
      show-password
      ></el-input>
      <el-divider></el-divider>
      <el-button 
      type="primary" 
      @click="setWifi()"
      >OK</el-button>
    </el-dialog>
</el-drawer>

</template>

<script>
import {mapGetters} from 'vuex'
export default {
    data: function(){
        return {
            drawer: true,
            showPasswordConfirm: false,
            password: '',
            wifi:'',
        }
    },
    computed:{
      ...mapGetters(['getNearWifi'])
    },
    mounted:function(){
        console.log("mount")
      this.$store.dispatch('updateNearWifi')
    },
    methods:{
      selectWifi: function(val){
        this.showPasswordConfirm = true
        this.wifi = val.ssid
      },
      setWifi: function(){
        console.log(this.wifi, this.password)
      this.$store.dispatch('setWifi',{
        _ssid: this.wifi,
        _sspw: this.password
      })

      }
    }
}
</script>

<style>

</style>