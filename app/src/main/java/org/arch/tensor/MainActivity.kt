package org.arch.tensor

import android.content.res.AssetManager
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import org.arch.tensor.databinding.ActivityMainBinding

class MainActivity : AppCompatActivity() {

    private lateinit var binding: ActivityMainBinding

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)

        initializeTensor(assets);
    }

    override fun onDestroy() {
        super.onDestroy()

        destroyTensor();
    }

    /**
     * A native method that is implemented by the 'tensor' native library,
     * which is packaged with this application.
     */
    external fun initializeTensor(assets: AssetManager): Unit
    external fun destroyTensor(): Unit

    companion object {
        // Used to load the 'tensor' library on application startup.
        init {
            System.loadLibrary("tensor")
        }
    }
}